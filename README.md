---
author: Dr Franck P. Vidal
institute: School of Computer Science and Electronic Engineering, Bangor University, UK
title: ICE4131 -- High Performance Computing
subtitle: A Simple ray tracer to parallelise using PThread, OpenMP, MPI and CUDA.
---

# SimpleRayTracing

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/2e8c4fd913234f2d880c43716c17cea9)](https://app.codacy.com/manual/effepivi/SimpleRayTracing?utm_source=github.com&utm_medium=referral&utm_content=effepivi/SimpleRayTracing&utm_campaign=Badge_Grade_Dashboard)

A simple ray-tracer used as an example of application for my HPC module. The code was executed on two of my desktop PCs, with two different CPUs, using GNU/Linux openSUSE Leap 15.2.
The same code was also executed on [Supercomputing Wales](https://www.supercomputing.wales/) with two different compilers (g++ 4.8.5 released in 2015 and icc 19.1.2.254 released in 2020).

| Model name:        | AMD FX(tm)-8350 Eight-Core Processor | Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz | Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz               |
|--------------------|--------------------------------------|------------------------------------------|--------------------------------------------------------|
| CPU MHz:           | 4000.000                             | 4900.956                                 | 2401.000                                               |
| CPU max MHz:       | 4000.0000                            | 5000.0000                                | 2401.000                                               |
| CPU min MHz:       | 1400.0000                            | 800.0000                                 | 1000.0000                                              |
| L1d cache:         | 16K                                  | 32K                                      | 32K                                                    |
| L1i cache:         | 64K                                  | 32K                                      | 32K                                                    |
| L2 cache:          | 2048K                                | 256K                                     | 1024K                                                  |
| L3 cache:          | 8192K                                | 16384K                                   | 28160K                                                 |
| NUMA node0 CPU(s): | 0-7                                  | 0-15                                     | 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38 |
| NUMA node1 CPU(s): | none                                 | none                                     | 1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39 |

| Processor                                      | Release date | Parallelisation     | Release | Debug | Compiler       |
|------------------------------------------------|--------------|---------------------|---------|-------|----------------|
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 80.0 | 85 | 396  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 40.0 | 85 | 406  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 24.0 | 124 | 627  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 16.0 | 179 | 918  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 8.0 | 352 | 1819  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 4.0 | 657 |  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 1.0 | 2518 |  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 80.0 | 86 | 441  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 40.0 | 87 | 452  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 24.0 | 143 | 680  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 16.0 | 185 | 995  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 8.0 | 365 | 1959  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 4.0 | 702 | 3659  |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | 1.0 | 2639 |  |

In the plot below, `x` depicts the runtime when the program is compiled in Release mode, and `+` in Debug mode.

![Plot of the runtimes](runtimes.png)
