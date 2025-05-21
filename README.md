#SYSTEM CALL
- 'make' in folder /src/userprog
- cd /userprog/build
- 'pintos-mkdisk filesys.dsk --filesys-size=2'
- 'pintos -f -q'.
- 'make' in folder /src/examples
- 'pintos -p ../src/examples/listmem -a listmem -- -q' 
- pintos -q run 'listmem'
- The program is not working yet. :((
