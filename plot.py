#!/usr/bin/env python3

import math

import pandas as pd

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

#matplotlib.use('Qt5Agg')

colours = list(mcolors.TABLEAU_COLORS);

df = pd.read_csv("runtimes.csv");


print("| Processor                                      | Release date | Parallelisation     | Release | Debug | Compiler       |")
print("|------------------------------------------------|--------------|---------------------|---------|-------|----------------|")
for processor in df["Processor"].unique():
    test1=df["Processor"] == processor;

    for compiler in df["Compiler"].unique():
        test2=df["Compiler"] == compiler;

        for thread_number in df[test1 & test2]["Number of threads"].unique():
            test3=df["Number of threads"] == thread_number;
            test_release=df["Compilation"] == "Release";
            test_debug=df["Compilation"] == "Debug";

            runtime_release = df[test1 & test2 & test3 & test_release]["Runtime in seconds"];
            runtime_debug   = df[test1 & test2 & test3 & test_debug]["Runtime in seconds"];

            i = [];
            for temp in runtime_release:
                i.append(round(temp));

            j = [];
            for temp in runtime_debug:
                j.append(round(temp));


            if processor == "Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz":
                release_date = "Q4 2018";
            elif processor == "Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz":
                release_date = "Q1 2018";
            elif processor == "AMD FX(tm)-8350 Eight-Core Processor @ 4.00GHz":
                release_date = "Q4 2012";

            parallelisation = "none";
            if thread_number == 1:
                parallelisation = "OpenMP with 1 thread";
            elif thread_number > 0:
                parallelisation = "OpenMP with " + str(int(thread_number)) + " threads";

            if len(i) and len(j):
                print("|", processor, "|", release_date, "|", parallelisation, "|", i[0], "|", j[0], " |", compiler, "|");
            elif len(i):
                print("|", processor, "|", release_date, "|", parallelisation, "|", i[0], "|",  " |", compiler, "|");
            elif len(j):
                print("|", processor, "|", release_date, "|", parallelisation, "|",  "|", j[0], " |", compiler, "|");


fig = plt.figure(figsize=(11, 6));
ax = plt.subplot(111);

colour_id = 1;

for processor in df["Processor"].unique():
    test1=df["Processor"] == processor;

    for compiler in df["Compiler"].unique():
        test3=df["Compiler"] == compiler;

        i = 0;
        for compilation in df["Compilation"].unique():
            test2=df["Compilation"] == compilation;

            X = [];
            Y = [];

            x = df[test1 & test2 & test3]["Number of threads"];
            y = df[test1 & test2 & test3]["Runtime in seconds"];

            for temp_x, temp_y in zip(x, y):
                if not math.isnan(temp_y):
                    X.append(temp_x);
                    Y.append(temp_y);

            if len(X) and len(Y):

                marker='x';
                if i == 1:
                    marker = '+';

                if compilation == "Release":
                    plt.plot(X, Y, color=colours[colour_id], label=processor + " (compiler: " + compiler + ")");
                    plt.scatter(X, Y, color=colours[colour_id], marker=marker);
                else:
                    plt.plot(X, Y, color=colours[colour_id], marker=marker);
            i += 1;

        if len(df[test1 & test3]) > 0:
            colour_id += 1;


ax.legend(loc='upper center', bbox_to_anchor=(0.5, 1.05),
          ncol=1, fancybox=True, shadow=True);

plt.xticks(df["Number of threads"].unique());

plt.xlabel('Number of threads');
plt.ylabel('Runtime in seconds');

plt.savefig('runtimes.pdf');
plt.savefig('runtimes.png');


fig = plt.figure(figsize=(11, 6));
ax = plt.subplot(111);

colour_id = 1;

test4=df["Number of threads"] == 0;
for processor in df["Processor"].unique():
    test1=df["Processor"] == processor;

    for compiler in df["Compiler"].unique():
        test3=df["Compiler"] == compiler;

        i = 0;
        for compilation in df["Compilation"].unique():
            test2=df["Compilation"] == compilation;

            X = [];
            Y = [];

            x = df[test1 & test2 & test3]["Number of threads"];
            y = df[test1 & test2 & test3]["Runtime in seconds"];

            reference_set = df[test1 & test2 & test3 & test4]["Runtime in seconds"];

            if len(reference_set):


                for ref in reference_set:
                    reference = ref;

                for temp_x, temp_y in zip(x, y):
                    if not math.isnan(temp_y):
                        X.append(temp_x);
                        Y.append(reference / temp_y);

                if len(X) and len(Y):

                    marker='x';
                    if i == 1:
                        marker = '+';

                    if compilation == "Release":
                        plt.plot(X, Y, color=colours[colour_id], label=processor + " (compiler: " + compiler + ")");
                        plt.scatter(X, Y, color=colours[colour_id], marker=marker);
            i += 1;

        if len(df[test1 & test3]) > 0:
            colour_id += 1;

plt.plot([0, 40], [1, 40], color=colours[colour_id], label="Theoretical speedup");


ax.legend(loc='lower right',
          ncol=1, fancybox=True, shadow=True);

plt.xticks(df["Number of threads"].unique());

plt.xlabel('Number of threads');
plt.ylabel('Speedup');

plt.savefig('speedup.pdf');
plt.savefig('speedup.png');


plt.show();
