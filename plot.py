#!/usr/bin/env python3

import math

import pandas as pd

import matplotlib
import matplotlib.pyplot as plt

matplotlib.use('Qt5Agg')

df = pd.read_csv("runtimes.csv");

fig = plt.figure(figsize=(11, 6));
ax = plt.subplot(111);


for processor in df["Processor"].unique():
    test1=df["Processor"] == processor;

    for compilation in df["Compilation"].unique():
        test2=df["Compilation"] == compilation;
        
        for compiler in df["Compiler"].unique():
            test3=df["Compiler"] == compiler;

            X = [];
            Y = [];
            
            x = df[test1 & test2 & test3]["Number of threads"];
            y = df[test1 & test2 & test3]["Runtime in seconds"];
            
            for temp_x, temp_y in zip(x, y):
                if not math.isnan(temp_y):
                    X.append(temp_x);
                    Y.append(temp_y);

            if len(X) and len(Y):
                plt.plot(X, Y, label=processor + " (compiler: " + compiler + ", compilation: " + compilation + ")");


ax.legend(loc='upper center', bbox_to_anchor=(0.5, 1.05),
          ncol=1, fancybox=True, shadow=True);

plt.xticks(df["Number of threads"].unique());

plt.xlabel('Number of threads');
plt.ylabel('Runtime in seconds');

plt.savefig('runtimes.pdf');
plt.savefig('runtimes.png');

plt.show();
