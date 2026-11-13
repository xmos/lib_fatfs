
#################################
lib_fatfs: FAT filesystem library
#################################

************
Introduction
************

``lib_fatfs`` packages ChaN's `FatFs <https://elm-chan.org/fsw/ff/>`_ module for XCORE
applications built with XCommon CMake. It adds an xcore default configuration and a way for
an application to change it; the FatFs source itself is unmodified.

This document covers only what is specific to ``lib_fatfs``. For the FatFs API, its
configuration options and the disk I/O interface, see the
`FatFs documentation <https://elm-chan.org/fsw/ff/>`_.

Accessing the library software
==============================

There are two ways to access the software in this library:

- Download the latest release ZIP package from the `XMOS Website <https://www.xmos.com/libraries/>`_ and extract it to a chosen sandbox directory.
- Clone the Git repository from `XMOS GitHub <https://github.com/xmos>`_.

The ZIP file download is the recommended option for most users, as it is a quick way to get started with the library.

*****
Usage
*****

``lib_fatfs`` is intended to be used with the `XCommon CMake <https://www.xmos.com/file/xcommon-cmake-documentation/?version=latest>`_
, the `XMOS` application build and dependency management system.

To use this library in an application include ``lib_fatfs`` in the application's ``APP_DEPENDENT_MODULES`` list in
`CMakeLists.txt`, for example:

.. code-block:: cmake

    set(APP_DEPENDENT_MODULES "lib_fatfs")

.. note:: Dependent modules should be pinned to release versions where possible, otherwise the
   latest commit on the `develop` branch will be used.  For further details on managing modules,
   pinning to a release version and other options, please see the page `xcommon-cmake Dependency Management <https://www.xmos.com/documentation/XM-015090-PC/html/doc/dependency_management.html>`_.

The FatFs API is accessed via the ``ff.h`` header file, and the disk interface via ``diskio.h``,
for example:

.. code-block:: C

    #include "ff.h"
    #include "diskio.h"

The application supplies the storage driver: ``disk_initialize``, ``disk_status``,
``disk_read``, ``disk_write`` and ``disk_ioctl``, together with ``get_fattime`` for file
timestamps. The example application shows a minimal set of these functions for a RAM disk.

FatFs is not reentrant in this configuration. Make all FatFs calls from one task, or serialise
them in the application.

*************
Configuration
*************

The defaults are in ``lib_fatfs/api/fatfs_config.h``: up to eight volumes addressed as
``"0:"`` to ``"7:"``, 512-byte sectors, FAT12/16/32, short (8.3) file names with code page 437,
read and write access, and formatting with ``f_mkfs``. exFAT, long file names, file locking and
64-bit sector addresses are disabled.

To change an option, add a ``fatfs_conf.h`` header to the application's include path and define
the options to change. Options that it does not define keep their defaults. For example, to
enable long file names:

.. code-block:: C

    #define FF_USE_LFN 1

Two options need functions that the application must supply, because they depend on its
memory allocator or operating system: ``FF_USE_LFN 3`` needs ``ff_memalloc`` and ``ff_memfree``,
and ``FF_FS_REENTRANT 1`` needs the ``ff_mutex_*`` functions. See the FatFs documentation.

Do not edit ``fatfs_config.h`` or upstream ``ffconf.h`` to configure an application. The same
configuration must be visible to every source file that includes ``ff.h``; XCommon CMake
arranges this for an application-level ``fatfs_conf.h``.

*******************
Example application
*******************

The ``app_fatfs_ramdisk`` example formats a RAM disk, writes a file and reads it back. It needs
no storage hardware.

Building the example
====================

This section assumes that the `XMOS XTC Tools <https://www.xmos.com/software-tools/>`_ have been
downloaded and installed. The required version is specified in the accompanying ``README``.

Installation instructions can be found `here <https://xmos.com/xtc-install-guide>`_.

Special attention should be paid to the section on
`Installation of Required Third-Party Tools <https://www.xmos.com/documentation/XM-014363-PC/html/installation/install-configure/install-tools/install_prerequisites.html>`_.

The application is built using the `xcommon-cmake <https://www.xmos.com/file/xcommon-cmake-documentation/?version=latest>`_
build system, which is provided with the XTC tools and is based on `CMake <https://cmake.org/>`_.

The ``lib_fatfs`` software ZIP package should be downloaded and extracted to a chosen working
directory.

To configure the build, the following commands should be run from an XTC command prompt:

.. tab:: Windows

    .. code-block:: console

        cd lib_fatfs\examples\app_fatfs_ramdisk
        cmake -G "Unix Makefiles" -B build

.. tab:: MacOS and Linux

    .. code-block:: console

        cd lib_fatfs/examples/app_fatfs_ramdisk
        cmake -G "Unix Makefiles" -B build

If any dependencies are missing they will be retrieved automatically during this step.

The application binary should then be built using ``xmake``:

.. code-block:: console

    xmake -j -C build

The binary (``app_fatfs_ramdisk.xe``) will be generated in the ``bin`` directory of the
``app_fatfs_ramdisk`` directory. By default it is built for the XK-EVK-XU316 board; pass
``-DAPP_HW_TARGET=<target>`` to ``cmake`` to build for another board.

For subsequent builds, the ``cmake`` step may be omitted.
If ``CMakeLists.txt`` or other build files are modified, ``cmake`` will be re-run automatically
by ``xmake`` as needed.

Running the example
===================

.. tab:: Windows

    From an XTC command prompt, the following command should be run from the
    ``examples\app_fatfs_ramdisk`` directory:

    .. code-block:: console

        xrun --io .\bin\app_fatfs_ramdisk.xe

    Alternatively, the application can be run in the simulator:

    .. code-block:: console

        xsim .\bin\app_fatfs_ramdisk.xe

.. tab:: MacOS and Linux

    From an XTC command prompt, the following command should be run from the
    ``examples/app_fatfs_ramdisk`` directory:

    .. code-block:: console

        xrun --io ./bin/app_fatfs_ramdisk.xe

    Alternatively, the application can be run in the simulator:

    .. code-block:: console

        xsim ./bin/app_fatfs_ramdisk.xe

The application prints:

.. code-block:: console

    HELLO.TXT: Hello from lib_fatfs!

*************
API Reference
*************

``lib_fatfs`` does not change the FatFs API. See the
`FatFs application interface documentation <https://elm-chan.org/fsw/ff/>`_ for the file system
functions and the disk I/O functions the application must supply.
