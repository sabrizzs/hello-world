# Estudos P2 SO

# Arquivos

## Organização de arquivos

### Organização de arquivos: organização interna

#### Unix block
- Sequencia de blocos, mas endereçada por bytes (acesso em bytes)
- Os comandos "read", "write" e "seek" são usados para ler, escrever e posicionar o cursor em um determinado byte dentro do arquivo, respectivamente.

#### QSAM (Queued Sequencial Access Method)
- Os arquivos são organizados por blocos físicos
- Acesso do usuário por registro lógico definido pelo usuário 

#### ISAM (Indexed Sequencial Access Method)
- Organização em árvore: blocos com número fixo de registros
- Cada bloco contém apontadores para outros blocos, permitindo o acesso sequencial pelo índice. 
- Adequado para operações de busca rápida em grandes arquivos, pois utiliza a estrutura de árvore para otimizar o acesso aos registros. 

![image](https://github.com/sabrizzs/hello-world/assets/93349105/92cfb3f0-7d0b-42ba-946e-2ddf1d500f28)

Existem vários outros métodos de organização interna de arquivos desenvolvidos pela IBM, como XDAP, BDAM, BSAM, BPAM, VSAM e OAM. 

Nos sistemas derivados dos computadores pessoais, é comum utilizar o acesso aleatório aos arquivos, permitindo a leitura e gravação em qualquer posição do arquivo, juntamente com a organização dos dados em blocos.

## Tipos de arquivos

#### Arquivos Regulares
Os arquivos regulares podem ser divididos em arquivos de caracteres (ASCII) e arquivos binários.

##### Arquivos de caracteres (ASCII):
- Esses arquivos contêm texto no formato ASCII, que é uma codificação padrão de caracteres utilizada em muitos sistemas. 
- Cada linha dentro do arquivo é terminada por "line feed" ou "carriage return" ou ambos, dependendo do sistema operacional. 
- As linhas podem ter tamanhos variáveis. 
- Os arquivos ASCII são úteis porque facilitam a manipulação de dados através de "pipes", que permitem conectar a saída de um arquivo à entrada de outro.

##### Arquivos binários: 
- Esses arquivos contêm dados em formato binário, que são interpretados de maneira diferente pelos sistemas operacionais em comparação com arquivos de caracteres. 
- Os arquivos binários são comumente usados para armazenar código executável, ou seja, programas que podem ser executados pelo sistema operacional. 
- Cada sistema operacional possui um formato específico para arquivos executáveis.

#### Archive (UNIX)
- No contexto do sistema operacional UNIX, um arquivo do tipo "Archive" é uma coleção de módulos de biblioteca que foram compilados, mas ainda não foram linkados. 
- Esses módulos de biblioteca são unidades independentes de código-fonte que podem ser reutilizadas em diferentes programas. 
- O arquivo "Archive" permite agrupar esses módulos em um único arquivo para facilitar sua distribuição e uso posterior.
- Cada módulo dentro do arquivo "Archive" possui entradas que contêm informações sobre o módulo:
- - Essas informações são armazenadas em um cabeçalho e geralmente incluem o nome do módulo, a data de criação, o proprietário, o código de proteção (permissões de acesso) e o tamanho do módulo.
- - Além do cabeçalho, o arquivo "Archive" também armazena os "object modules" (módulos objeto), que são as representações compiladas dos módulos de biblioteca.

#### Problema dos arquivos "fortemente tipados".
Isso se refere a situações em que um programa ou ferramenta gera um arquivo com uma extensão de arquivo específica que não é reconhecida ou aceita por outras ferramentas do sistema. 

Por exemplo, suponha que um pré-processador de linguagem C (ou C++) gere um programa em linguagem C, mas o salve com a extensão .dat em vez da extensão .c esperada pelo compilador C.

## Atributos comuns em arquivos

Atributos comuns em arquivos são características ou metadados associados a um arquivo para fornecer informações adicionais sobre ele. Esses atributos podem variar dependendo do sistema operacional e do sistema de arquivos utilizado. Abaixo estão alguns atributos comuns encontrados em arquivos:

- Proteção: Indica as permissões de acesso ao arquivo, especificando quem pode ler, escrever ou executar o arquivo.

- Senha específica: Algumas vezes, um arquivo pode ser protegido por uma senha específica para restringir o acesso somente a usuários autorizados.

- Criador (usuário): Identifica o usuário que criou o arquivo.

- Dono (usuário): Indica o proprietário atual do arquivo.

- Flag de leitura/escrita: Em sistemas Unix, essas flags indicam se o arquivo pode ser lido ou modificado.

- Flag de "hidden file": Indica se o arquivo deve ser ocultado e não exibido por padrão nos navegadores de arquivos.

- System flag: Uma flag que sinaliza que o arquivo é um arquivo do sistema, geralmente relacionado ao funcionamento interno do sistema operacional.

- ASCII/Binary flag: Indica se o conteúdo do arquivo é texto em formato ASCII ou se é um arquivo binário que contém dados não textuais.

- Archive flag: Essa flag pode indicar se o arquivo foi marcado para backup ou se foi alterado desde o último backup.

- Random access flag: Indica se o arquivo suporta acesso aleatório aos seus dados, permitindo leitura ou gravação em qualquer posição dentro do arquivo.

- Temporary flag: Indica se o arquivo é temporário e pode ser removido automaticamente quando não estiver mais em uso.

- Lock flag: Uma flag que indica se o arquivo está bloqueado para impedir alterações ou acesso concorrente.

- Tamanho do registro: Aplica-se a arquivos formatados, especifica o tamanho fixo de cada registro no arquivo.

- Key position: Aplica-se a arquivos formatados com campos de chave, indica a posição da chave em cada registro.

- Key length: Aplica-se a arquivos formatados, especifica o tamanho da chave em cada registro.

- Criação: Indica a data e hora em que o arquivo foi criado.

- Último acesso: Registra a data e hora do último acesso ao arquivo.

- Última alteração: Indica a data e hora da última modificação do arquivo.

- Tamanho atual: Representa o tamanho atual do arquivo em bytes.

- Tamanho máximo: Em alguns sistemas, é possível definir um tamanho máximo para o arquivo, embora seja incomum em sistemas modernos.

## Operações em arquivos

Operações em arquivos são ações que podem ser realizadas em arquivos dentro de um sistema de arquivos. Abaixo estão as principais operações em arquivos:

- Criação: É a operação de criar um novo arquivo no sistema de arquivos. Nessa operação, um espaço é alocado para armazenar o conteúdo do arquivo e os atributos são definidos.

- Remoção: É a operação de excluir um arquivo existente do sistema de arquivos. Isso envolve a liberação de espaço ocupado pelo arquivo e a remoção de suas entradas de metadados.

- Abertura: É a operação de abrir um arquivo existente para leitura ou escrita. Durante a abertura, são verificadas a disponibilidade do arquivo, suas permissões de acesso e é estabelecida uma associação entre o arquivo e o processo que o abriu. Também é criada uma estrutura de controle para rastrear informações sobre o acesso ao arquivo.

- Fechamento (close): É a operação de encerrar o acesso a um arquivo aberto. Nesse estágio, as alterações pendentes são gravadas no disco, os recursos associados ao arquivo são liberados e a estrutura de controle é atualizada.

- Leitura: É a operação de ler o conteúdo de um arquivo. O usuário pode precisar especificar o tamanho da leitura, especialmente em arquivos não formatados em registros. É necessário fornecer uma área de armazenamento para os dados lidos.

- Escrita: É a operação de gravar dados em um arquivo. Os dados são gravados em um buffer, e se o final do bloco é atingido, o conteúdo do buffer é gravado no disco. Se o arquivo estiver no final, o tamanho do arquivo é aumentado, e se estiver no meio, os dados existentes podem ser sobrescritos.

- Append: É uma forma restrita de escrita, onde os dados são adicionados ao final do arquivo, sem a possibilidade de modificação em outras partes do arquivo.

- Seek: É uma operação usada em arquivos de acesso randômico, permitindo alterar a posição atual de leitura ou escrita no arquivo. Isso permite que o processo acesse registros em qualquer posição do arquivo.

- Pega atributos: É uma operação que retorna os atributos do arquivo, como proteção, tamanho, data de criação, entre outros. Essa informação é útil em várias situações, como em comandos de manipulação de arquivos.

- Seta atributos: É uma operação que permite a modificação dos atributos de um arquivo. Geralmente, essa operação é restrita e requer permissões adequadas.

- Renomear: É a operação de alterar o nome de um arquivo existente. Em vez de renomear diretamente, essa operação pode ser implementada copiando o conteúdo do arquivo para um novo arquivo com o nome desejado e, em seguida, removendo o arquivo antigo.

- Lock: É uma operação usada para restringir temporariamente o acesso a um arquivo ou parte dele. Isso evita que outros processos acessem ou modifiquem o arquivo simultaneamente, garantindo a integridade dos dados.

## Diretórios

Diretórios são conjuntos utilizados para agrupar arquivos em um sistema de arquivos. Eles permitem a organização e estruturação dos arquivos de forma hierárquica, facilitando a navegação e o gerenciamento dos dados.

Existem várias variações na forma como os diretórios são utilizados, dependendo do sistema operacional e das necessidades do usuário. Alguns exemplos são:

- Um diretório por sistema: Nesse caso, todos os arquivos do sistema são organizados em um único diretório raiz. Esse modelo era comum em sistemas mais antigos, como o MS-DOS.

- Um diretório por usuário: Cada usuário possui seu próprio diretório pessoal, onde pode armazenar seus arquivos de forma exclusiva. Isso é comum em sistemas operacionais multiusuários, como o Unix.

- Estrutura hierárquica: Os diretórios são organizados em uma estrutura de árvore ou grafo direcionado acíclico (DAG), permitindo a criação de subdiretórios dentro de diretórios. Essa estrutura é amplamente utilizada em sistemas operacionais modernos, como o Windows e o Linux.

- - Nomes absolutos: São nomes de arquivos ou diretórios que especificam o caminho completo a partir do diretório raiz até o arquivo desejado. Por exemplo, "/usr/local/bin/perl" é um nome absoluto que indica a localização exata do arquivo "perl" no sistema de arquivos.

- - Nomes relativos: São nomes de arquivos ou diretórios que são especificados em relação ao diretório atual em que o processo está trabalhando. Por exemplo, "fotos/noisNaFoto.jpg" é um nome relativo que indica que o arquivo "noisNaFoto.jpg" está localizado dentro do diretório "fotos" no diretório atual. Nomes relativos implicam a existência de um "diretório corrente" mantido para cada processo.

### Operações em Diretórios

Operações em diretórios envolvem a manipulação e gerenciamento dos diretórios em um sistema de arquivos. Aqui estão algumas operações comuns em diretórios:

- Criação: Essa operação permite a criação de um novo diretório vazio. Ao criar um diretório (Unix), geralmente são adicionadas duas entradas especiais: "." representa o diretório atual e ".." representa o diretório pai.

- Remoção: Essa operação permite a remoção de um diretório. Em Unix, para remover um diretório, ele precisa estar vazio, ou seja, não deve conter nenhum arquivo ou subdiretório.

- Abertura: Um diretório pode ser aberto para leitura. Isso permite que o conteúdo do diretório seja lido, incluindo as informações sobre os arquivos e subdiretórios presentes nele.

- Fechamento: Após a leitura ou manipulação de um diretório, ele pode ser fechado para liberar recursos e encerrar a operação.

- Leitura (readdir): A operação de leitura em um diretório permite ler a próxima entrada do diretório. Cada entrada corresponde a um arquivo ou subdiretório contido no diretório. Essa operação é útil para listar o conteúdo de um diretório.

- Renomear: Essa operação permite renomear um diretório. O diretório é identificado pelo seu nome atual e pode ser renomeado para um novo nome especificado pelo usuário.

- Link: A operação de link permite criar links para um arquivo ou diretório. Existem dois tipos principais de links:

- - Hard links: Com um hard link, duas ou mais entradas diferentes no sistema de arquivos apontam para o mesmo descritor de arquivo. Isso facilita o compartilhamento de arquivos, pois eles não são removidos até que todas as entradas que apontam para eles sejam removidas. No entanto, o uso de hard links pode ter implicações de segurança, pois alguém pode manter um arquivo vivo mesmo que o proprietário original queira removê-lo. Além disso, os hard links são limitados a um único sistema de arquivos.

- - Soft links (também conhecidos como symbolic links ou symlinks): Um soft link é uma entrada especial em um diretório que contém o endereço absoluto ou relativo de outra entrada em um diretório. Ao contrário dos hard links, os soft links podem ser usados em diferentes sistemas de arquivos. Se o arquivo apontado por um soft link for removido, o link se tornará inválido. Isso pode ser vantajoso em termos de segurança, pois a remoção do link não afeta diretamente o arquivo, mas pode se tornar um problema se o arquivo original for movido ou renomeado.

- Unlink: A operação de unlink é usada para remover uma entrada de diretório. Ao remover uma entrada, seja um arquivo ou um link, ela é excluída do diretório, mas o arquivo em si não é necessariamente removido imediatamente. A remoção real do arquivo ocorre quando todas as entradas que apontam para ele são removidas.

## Implementação de sistemas de arquivos










