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
The code produces an 2048x2048 image as follows:

![Rendered image.](test.jpg)

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
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 80 threads | 85 | 396  | g++ 4.8.5 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 40 threads | 85 | 406  | g++ 4.8.5 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 24 threads | 124 | 627  | g++ 4.8.5 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 16 threads | 179 | 918  | g++ 4.8.5 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 8 threads | 352 | 1819  | g++ 4.8.5 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 4 threads | 657 | 3479  | g++ 4.8.5 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 1 thread | 2518 |  | g++ 4.8.5 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | none | 2692 |  | g++ 4.8.5 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 80 threads | 86 | 441  | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 40 threads | 87 | 452  | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 24 threads | 143 | 680  | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 16 threads | 185 | 995  | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 8 threads | 365 | 1959  | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 4 threads | 702 | 3659  | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | OpenMP with 1 thread | 2639 |  | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz | Q1 2018 | none | 2683 |  | icc 19.1.2.254 |
| AMD FX(tm)-8350 Eight-Core Processor | Q1 2018 | OpenMP with 80 threads | 585 |  | gcc 7.5.0 |
| AMD FX(tm)-8350 Eight-Core Processor | Q1 2018 | OpenMP with 40 threads | 586 |  | gcc 7.5.0 |
| AMD FX(tm)-8350 Eight-Core Processor | Q1 2018 | OpenMP with 24 threads | 583 |  | gcc 7.5.0 |
| AMD FX(tm)-8350 Eight-Core Processor | Q1 2018 | OpenMP with 16 threads | 587 |  | gcc 7.5.0 |
| AMD FX(tm)-8350 Eight-Core Processor | Q1 2018 | OpenMP with 8 threads | 606 |  | gcc 7.5.0 |
| AMD FX(tm)-8350 Eight-Core Processor | Q1 2018 | OpenMP with 4 threads | 1050 |  | gcc 7.5.0 |
| AMD FX(tm)-8350 Eight-Core Processor | Q1 2018 | OpenMP with 1 thread | 3981 |  | gcc 7.5.0 |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz | Q4 2018 | OpenMP with 80 threads | 199 |  | gcc 7.5.0 |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz | Q4 2018 | OpenMP with 40 threads | 204 |  | gcc 7.5.0 |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz | Q4 2018 | OpenMP with 24 threads | 208 |  | gcc 7.5.0 |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz | Q4 2018 | OpenMP with 16 threads | 209 |  | gcc 7.5.0 |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz | Q4 2018 | OpenMP with 8 threads | 287 |  | gcc 7.5.0 |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz | Q4 2018 | OpenMP with 4 threads | 515 |  | gcc 7.5.0 |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz | Q4 2018 | OpenMP with 1 thread | 1911 |  | gcc 7.5.0 |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz | Q4 2018 | none | 1884 |  | gcc 7.5.0 |

In the plot below, `x` depicts the runtime when the program is compiled in Release mode, and `+` in Debug mode.

![Plot of the runtimes](runtimes.png)
