FAT16 reader
============

A FAT16 filesystem reader in C. Work in progress.

Because I didn't know much about filesystems and I didn't know much C. I still don't know enough C, but I now know more than I'd like to about FAT16 and friends.


Output
------

Here's the output for the included sample.fat16 filesytem image:

    Boot sector size: 8 bytes
    Jump instruction: EB 3C 90
    OEM name: mkdosfs

    BIOS parameters:
      Bytes per sector: 512
      Sectors per cluster: 4
      Reserved sectors: 4
      Number of FATs: 2
      Maximum root entries: 512
      Total sectors: 32768 (small: 32768, large: 0)
      Media descriptor: 0xF8 (fixed disk)
      Sectors per FAT: 32
      Sectors per track: 32
      Number of heads: 64
      Sectors before partition: 0

    Extended BIOS parameters:
      Physical drive code: 0x00 (removable)
      Reserved byte (WinNT): 0x00
      Extended boot signature: 0x29
      Volume serial number: 0x365AF7C9
      Volume label: BlargDisk
      FAT type: FAT16
      OS boot code: 448 bytes
      Boot sector signature: 0x0055

    Calculated parameters:
      FAT size: 16384 bytes
      FAT #1 offset: 0x00000800
      FAT #2 offset: 0x00004800
      Root directory offset: 0x00008800
      Root directory size: 16384 bytes
      Data offset: 0x0000C800
      Cluster size: 2048 bytes

    Root directory:
      DOCS
        bytes: 0  cluster: 3
        created:  2011-08-26 20:21:10
        modified: 2011-08-26 20:21:10
        accessed: 2011-08-26
        ro:no hide:no sys:no dir:yes arch:no
      L33T.NFO
        bytes: 14  cluster: 5
        created:  2011-08-26 20:22:08
        modified: 2011-08-26 20:22:08
        accessed: 2011-08-26
        ro:no hide:no sys:no dir:no arch:yes
        Content:
    more content!
        <EOF>


Meh
---

© 2011 Paul Annesley
MIT license; free open source.
