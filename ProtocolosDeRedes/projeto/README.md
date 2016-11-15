[Tutorial](https://www.cs.rutgers.edu/~pxk/417/notes/sockets/udp.html)

## Para compilar

Versão cliente:
```
$ gcc cliente.c extras/md5.c extras/config.c -o cliente
$ ./cliente
```

Versão servidor:
```
$ gcc servidor.c extras/md5.c extras/config.c -o servidor
$ ./servidor
```