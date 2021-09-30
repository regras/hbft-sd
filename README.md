# mrsh-hbft
Approximate matching using Hierarchical Bloom Filter Trees. Based on [mrsh-v2](https://www.fbreitinger.de/?page_id=218) by [Frank Breitinger](https://www.fbreitinger.de).

## Relevant Publications
D. Lillis, F. Breitinger, M. Scanlon, Expediting MRSH-v2 Approximate Matching with Hierarchical Bloom Filter Trees. In: Matoušek P., Schmiedecker M. (eds) Digital Forensics and Cyber Crime. ICDF2C 2017. Lecture Notes of the Institute for Computer Sciences, Social Informatics and Telecommunications Engineer- ing, vol 216. Springer, Cham, 2018 (doi: [10.1007/978-3-319-73697-6_11](https://dx.doi.org/10.1007/978-3-319-73697-6_11)).

D. Lillis, F. Breitinger and M. Scanlon. Hierarchical Bloom Filter Trees for Approximate Matching. Journal of Digital Forensics, Security and Law (JDFSL), 13(1), 2018.

# hbft-sd 
Esta é uma modificação do mrsh-hbft, na qual o módulo de extração de features originalmente do mrsh-v2 foi trocado pelo sdhash.

### Instruções
### Para o sdhash é preciso a biblioteca boost
1. Baixe de https://www.boost.org/users/history/version_1_73_0.html

2. Extraia na pasta /usr/local/ com o comando?

```
tar --bzip2 -xf boost_1_75_0.tar.bz2 - C/usr/local/
```

3. Na pasta /usr/local/ execute:
```
$ sudo ./bootstrap.sh
```
```
$ sudo ./b2 install
```
### Para compilar
1. Execute
```
cmake ./
```
2. Execute
```
make
```
O executável gerado se encontrará na pasta bin

### Para executar
1. Execute
```
./mrsh-hbft
```

#### Observações sobre os parâmetros

1.Parâmetros como blocksize e min_run estão definidos no arquivo test.c, e não no config.h

2.O parâmetro BF_SIZE_IN_BYTES não é utilizado no test.c, apenas no arquivo main.c que supostamente iria ser o novo main mas a mudança não foi realizada ainda.

3.O parâmetro de memória no test.c é o que muda o tamanho dos filtros a serem utilizados.

4.Para mudar o tipo de árvore, com filtros variáveis ou fixos, é necessário alterar o define no arquivo config.h
