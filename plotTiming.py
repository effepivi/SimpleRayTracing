#!/usr/bin/env python3

import math

import pandas as pd
import numpy as np

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

#matplotlib.use('Qt5Agg')


def printRawTable(df):

    print("| Processor                                      | Release date | Parallelisation     | Compiler | Runtime in sec |")
    print("|------------------------------------------------|--------------|---------------------|----------|----------------|")
    for processor in df["CPU"].unique():
        test_Processor=df["CPU"] == processor;

        for compiler in df[test_Processor]["Compiler"].unique():
            test_Compiler=df["Compiler"] == compiler;

            for parallelisation in df[test_Processor & test_Compiler]["Parallelisation"].unique():
                test_Parallelisation=df["Parallelisation"] == parallelisation;

                for nodes in np.sort(df[test_Processor & test_Compiler & test_Parallelisation]["Number of nodes"].unique()):
                    test_Nodes=df["Number of nodes"] == nodes;

                    for thread_number in np.sort(df[test_Processor & test_Compiler & test_Parallelisation & test_Nodes]["Number of threads per node"].unique()):
                        test_thread_number=df["Number of threads per node"] == thread_number;

                        runtime = df[test_Processor & test_Compiler & test_Parallelisation & test_Nodes & test_thread_number]["Runtime in sec"]; # / 60;

                        #print(runtime)
                        i = [];
                        for temp in runtime:
                            #i.append(round(temp));
                            i.append(temp);

                        if processor == "Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz":
                            release_date = "Q4 2018";
                        elif processor == "Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz":
                            release_date = "Q1 2018";
                        elif processor == "AMD FX(tm)-8350 Eight-Core Processor @ 4.00GHz":
                            release_date = "Q4 2012";

                        parallelisation_string = parallelisation;

                        if thread_number == 1:
                            parallelisation_string += " with 1 thread";
                        elif thread_number > 1:
                            parallelisation_string += " with " + str(int(thread_number)) + " threads";

                        if nodes > 1:
                            parallelisation_string += " on " + str(nodes) + " nodes";

                        print("|", processor, "|", release_date, "|", parallelisation_string, " |", compiler, "|", i[0], "|");


def displayRuntime(df):
    fig = plt.figure(figsize=(11, 6));
    ax = plt.subplot(111);

    colour_id = 1;

    for processor in df["CPU"].unique():
        test_Processor=df["CPU"] == processor;

        for compiler in df[test_Processor]["Compiler"].unique():
            test_Compiler=df["Compiler"] == compiler;

            for parallelisation in df[test_Processor & test_Compiler]["Parallelisation"].unique():
                test_Parallelisation=df["Parallelisation"] == parallelisation;

                for nodes in np.sort(df[test_Processor & test_Compiler & test_Parallelisation]["Number of nodes"].unique()):
                    test_Nodes=df["Number of nodes"] == nodes;

                    X = [];
                    Y = [];

                    for thread_number in np.sort(df[test_Processor & test_Compiler & test_Parallelisation & test_Nodes]["Number of threads per node"].unique()):
                        test_thread_number=df["Number of threads per node"] == thread_number;

                        runtime = df[test_Processor & test_Compiler & test_Parallelisation & test_Nodes & test_thread_number]["Runtime in sec"]; # / 60;

                        #print(runtime)
                        i = [];
                        for temp in runtime:
                            #i.append(round(temp));
                            Y.append(temp);
                            X.append(thread_number);

                        parallelisation_string = parallelisation;

                        if nodes > 1:
                            parallelisation_string += " on " + str(nodes) + " nodes";

                    if len(X) and len(Y):

                        marker='x';

                        plt.plot(X, Y, color=colours[colour_id], label=parallelisation_string);
                        plt.scatter(X, Y, color=colours[colour_id], marker=marker);

                        colour_id += 1;


    ax.legend(loc='upper center', bbox_to_anchor=(0.5, 1.05),
              ncol=1, fancybox=True, shadow=True);

    plt.xticks(df["Number of threads per node"].unique());

    plt.xlabel('Number of threads');
    plt.ylabel('Runtime in seconds');

    plt.savefig('runtimes.pdf');
    plt.savefig('runtimes.png');


def displaySpeedup(df):
    fig = plt.figure(figsize=(11, 6));
    ax = plt.subplot(111);

    colour_id = 1;

    for processor in df["CPU"].unique():
        test_Processor=df["CPU"] == processor;

        for compiler in df[test_Processor]["Compiler"].unique():
            test_Compiler=df["Compiler"] == compiler;


            test1 = df["Parallelisation"] == "None";
            test2 = df["Number of threads per node"] == 0;
            test3 = df["Number of nodes"] == 1;
            reference = df[test_Compiler & test_Processor & test1 & test2 & test3]["Runtime in sec"];

            for parallelisation in df[test_Processor & test_Compiler]["Parallelisation"].unique():
                test_Parallelisation=df["Parallelisation"] == parallelisation;

                for nodes in np.sort(df[test_Processor & test_Compiler & test_Parallelisation]["Number of nodes"].unique()):
                    test_Nodes=df["Number of nodes"] == nodes;

                    X = [];
                    Y = [];

                    for thread_number in np.sort(df[test_Processor & test_Compiler & test_Parallelisation & test_Nodes]["Number of threads per node"].unique()):
                        test_thread_number=df["Number of threads per node"] == thread_number;

                        runtime = df[test_Processor & test_Compiler & test_Parallelisation & test_Nodes & test_thread_number]["Runtime in sec"]; # / 60;

                        #print(runtime)
                        i = [];
                        for temp in runtime:
                            Y.append(reference / temp);
                            X.append(thread_number);

                        parallelisation_string = parallelisation;

                        if nodes > 1:
                            parallelisation_string += " on " + str(nodes) + " nodes";

                    if len(X) and len(Y):

                        marker='x';

                        plt.plot(X, Y, color=colours[colour_id], label=parallelisation_string);
                        plt.scatter(X, Y, color=colours[colour_id], marker=marker);

                        colour_id += 1;


    plt.plot([0, 160], [1, 160], color=colours[colour_id], label="Theoretical speedup");


    ax.legend(loc='upper left',
              ncol=1, fancybox=True, shadow=True);

    plt.xticks(df["Number of threads per node"].unique());

    plt.xlabel('Number of threads per node');
    plt.ylabel('Speedup');

    plt.savefig('speedup.pdf');
    plt.savefig('speedup.png');


colours = list(mcolors.TABLEAU_COLORS);

df = pd.read_csv("timing.csv");
#printRawTable(df);
displayRuntime(df);
displaySpeedup(df);

plt.show();
