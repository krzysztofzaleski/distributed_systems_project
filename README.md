### Distributed Systems Project

# Project for studies

**Includes:**
- Concurrent computing
- Child processes
- 4 choices of programs to run (implemented in server)
- 4 programs: 
  * quotient
  * multiplying
  * sum
  * difference

**Compile:**
```
g++ serwer.c gniazdo.c -o serwer
g++ klient.c gniazdo.c -o klient
g++ witam.c -o witam
g++ lista.c -o lista

```

**Run:**
```
./serwer
./klient localhost ./<program name>
```
