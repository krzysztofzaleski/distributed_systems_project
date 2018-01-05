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
g++ iloraz.c -o iloraz
g++ iloczyn.c -o iloczyn
g++ suma.c -o suma
g++ roznica.c -o roznica
```

**Run:**
```
./serwer
./klient localhost
```
