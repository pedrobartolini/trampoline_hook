this was made by me when I was into game hacking </br>

### what it does
- scan game modules for an array of bytes and return address when found;
- allocates new code into game memoryspace;
- replace existent instruction in found address with jmp to newly added code, inserts jmp back to original address in end of newly added code;

### with this we can
- store/modify registers and memory at given time;


