This is an experimental bootloader set up for 2 stages, but currently has only one stage.
Interrupts(IDT and ISR) have been setup, there's a VGA driver and a keyboard driver.

A driver of sorts for ports and a system timer have been set up.

A fairly minimal libc has also been built
- Strings
- Memory

### Requirements
- qemu-i686
- cross-compiler for i686

### Make Commands
- make clean : remove all compiled object files
- make debug : build and run with remote gdb
- make run : build and run
