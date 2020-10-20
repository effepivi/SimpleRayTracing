#!/usr/bin/env python3

import math

import pandas as pd

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

#matplotlib.use('Qt5Agg')

colours = list(mcolors.TABLEAU_COLORS);

df = pd.read_csv("runtimes.csv");

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

plt.show();
