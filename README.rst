:orphan:

################################
lib_fatfs: FatFs wrapper library
################################

:vendor: XMOS
:version: 1.0.0
:scope: General use
:description: FatFs FAT filesystem integration for XCORE
:category: General purpose
:keywords: Memory
:devices: xcore-200, xcore.ai

*******
Summary
*******

This library integrates ChaN's FatFs filesystem module with XMOS XCORE projects.
It provides file and directory access on block storage through application-supplied
disk I/O callbacks.

********
Features
********

* FAT12, FAT16 and FAT32 filesystem support.
* File and directory operations, including read, write and formatting APIs.
* Hardware-independent disk interface for application-specific storage drivers.
* XMOS configuration maintained separately from the upstream source.
* Optional ``fatfs_conf.h`` application header to override any FatFs configuration option.
* CMake and legacy Make build integration.

************
Known issues
************

* None

****************
Development repo
****************

* `lib_fatfs <https://www.github.com/xmos/lib_fatfs>`_ (https://www.github.com/xmos/lib_fatfs)

**************
Required tools
**************

* XMOS XTC Tools 15.3.1

*********************************
Required libraries (dependencies)
*********************************

* None

****************
Third-party code
****************

This library uses FatFs.

* Original project: `FatFs <https://elm-chan.org/fsw/ff/00index_e.html>`_.
* Upstream Git mirror: `abbrev/fatfs <https://github.com/abbrev/fatfs>`_.
* XMOS fork: `xmosforks/FatFs <https://github.com/xmosforks/FatFs>`_.
* Upstream version: ``R0.16.post3`` (``R0.16`` with upstream patches 1 to 3).
  The source is not modified by XMOS.
* Location: ``third_party/FatFs``.

*************************
Related application notes
*************************

* None

*******
Support
*******

This package is supported by XMOS Ltd. Issues can be raised against the software at
`www.xmos.com/support <https://www.xmos.com/support>`_ or using GitHub `issues <https://github.com/xmos/lib_fatfs/issues>`_.
