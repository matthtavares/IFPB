/*
 * Simple MD5 implementation
 * @author creationix https://gist.github.com/creationix/4710780/
 * @update Mateus Tavares http://github.com/matthtavares
 * Compile with: gcc -o md5 -O3 -lm md5.c
 */

// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
 
// These vars will contain the hash
uint32_t h0, h1, h2, h3;
 
void md5(char *initial_msg, char *encoded);