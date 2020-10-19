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

| Processor:                                      | Release date | Parallelisation     | Release | Debug | Compiler       |
|-------------------------------------------------|--------------|---------------------|---------|-------|----------------|
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz        | Q4 2018      | None                | 992     | 2790  | g++ 7.5.0      |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz        | Q4 2018      | OpenMP (4 threads)  | 275     | 1313  | g++ 7.5.0      |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz        | Q4 2018      | OpenMP (8 threads)  | 151     | 711   | g++ 7.5.0      |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz        | Q4 2018      | OpenMP (16 threads) | 109     | 577   | g++ 7.5.0      |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz        | Q4 2018      | OpenMP (24 threads) | 105     | 563   | g++ 7.5.0      |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz        | Q4 2018      | OpenMP (40 threads) | 108     | 561   | g++ 7.5.0      |
| Intel(R) Core(TM) i9-9900K CPU @ 3.60GHz        | Q4 2018      | OpenMP (80 threads) | 103     | 562   | g++ 7.5.0      |
| AMD FX(tm)-8350 Eight-Core Processor @ 4.00GHz  | Q4 2012      | None                | 2001    |       | g++ 7.5.0      |
| AMD FX(tm)-8350 Eight-Core Processor @ 4.00GHz  | Q4 2012      | OpenMP (4 threads)  | 522     |       | g++ 7.5.0      |
| AMD FX(tm)-8350 Eight-Core Processor @ 4.00GHz  | Q4 2012      | OpenMP (8 threads)  | 311     |       | g++ 7.5.0      |
| AMD FX(tm)-8350 Eight-Core Processor @ 4.00GHz  | Q4 2012      | OpenMP (16 threads) | 305     |       | g++ 7.5.0      |
| AMD FX(tm)-8350 Eight-Core Processor @ 4.00GHz  | Q4 2012      | OpenMP (24 threads) | 305     |       | g++ 7.5.0      |
| AMD FX(tm)-8350 Eight-Core Processor @ 4.00GHz  | Q4 2012      | OpenMP (40 threads) |         |       | g++ 7.5.0      |
| AMD FX(tm)-8350 Eight-Core Processor @ 4.00GHz  | Q4 2012      | OpenMP (80 threads) |         |       | g++ 7.5.0      |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | None                |         |       | g++ 4.8.5      |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (4 threads)  |         |       | g++ 4.8.5      |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (8 threads)  |         |       | g++ 4.8.5      |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (16 threads) |         |       | g++ 4.8.5      |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (24 threads) |         |       | g++ 4.8.5      |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (40 threads) |         |       | g++ 4.8.5      |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (80 threads) |         |       | g++ 4.8.5      |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | None                |         |       | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (4 threads)  |         |       | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (8 threads)  |         |       | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (16 threads) |         |       | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (24 threads) |         |       | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (40 threads) |         |       | icc 19.1.2.254 |
| Intel(R) Xeon(R) Gold 6148 CPU @ 2.40GHz        | Q1 2018      | OpenMP (80 threads) |         |       | icc 19.1.2.254 |

![Plot of the runtimes](runtimes.png)
