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

### Layout de sistemas de aquivos 

Em discos, o layout típico começa com o Master Boot Record (MBR) seguido pela tabela de partições. O MBR é o primeiro setor do disco e contém um código de inicialização e a tabela de partições. A tabela de partições é uma estrutura que divide o disco em partições independentes.

Existem dois tipos principais de partições:

- Partições primárias: Nos sistemas PC, a tabela de partições permite até quatro entradas para partições primárias. Cada partição primária é tratada como uma unidade separada e pode conter um sistema de arquivos.

- Partições lógicas: Quando há a necessidade de criar mais de quatro partições no disco, pode-se usar partições lógicas. Essas partições são criadas dentro de uma partição primária especial chamada partição estendida. A partição estendida contém tabelas de subpartições que definem as partições lógicas dentro dela.

É importante observar que nem todos os dispositivos de armazenamento possuem partições. Alguns dispositivos, como unidades flash USB, podem não ter uma tabela de partições. Nesses casos, a BIOS lê o primeiro setor do dispositivo e procura por um "número mágico" específico para determinar se ele contém um código executável.

Cada partição é organizada independentemente e possui seu próprio "boot block". O boot block é a área de inicialização da partição e contém o código necessário para iniciar o sistema operacional a partir dessa partição específica.

A organização das partições em sistemas de arquivos varia de acordo com o sistema operacional.

### Unix

 No caso do Unix, existem componentes-chave que compõem a estrutura de um sistema de arquivos. 

- BootBlock: É a primeira parte do sistema de arquivos e contém um código de inicialização. Se o número mágico correto estiver presente, o BootBlock pode ser executado como um programa de inicialização.

- SuperBlock: O SuperBlock contém informações essenciais sobre o sistema de arquivos, como o tamanho do sistema de arquivos, o número de blocos e inodes disponíveis, o tamanho do bloco, a localização do RootDir (diretório raiz) e outras informações relacionadas à estrutura do sistema de arquivos. O SuperBlock é carregado na memória durante a inicialização do sistema ou quando o sistema de arquivos é acessado pela primeira vez.

- Free Space Management: Essa parte do sistema de arquivos é responsável por controlar os espaços livres disponíveis nos blocos de armazenamento. Ela mantém o controle de quais blocos estão ocupados por arquivos e quais estão disponíveis para armazenamento adicional.

- I-nodes: Os I-nodes (índices de nós) são estruturas de dados que representam arquivos e diretórios no sistema de arquivos Unix. Cada arquivo ou diretório tem um I-node associado a ele, que armazena informações como permissões, proprietário, tamanho, data e hora de criação, localização dos blocos de dados e outras metainformações. Os I-nodes são usados para localizar e acessar os dados reais dos arquivos.

- RootDir: O diretório raiz é o ponto de partida da estrutura de diretórios do sistema de arquivos. Ele contém os diretórios e arquivos principais do sistema, e sua localização é fixa para facilitar o acesso.

- Arquivos e Diretórios: Os arquivos e diretórios são os dados reais armazenados no sistema de arquivos. Os arquivos contêm os dados do usuário, enquanto os diretórios são estruturas que organizam e fornecem acesso aos arquivos. A estrutura de diretórios segue uma hierarquia em forma de árvore, permitindo a organização lógica dos arquivos e facilitando a navegação e busca.

![image](https://github.com/sabrizzs/hello-world/assets/93349105/a7639094-a1d4-4a2c-a674-274be9a83156)

### Alocação de arquivos Contínua

#### O que é?

A alocação de arquivos contínua é um método de implementação de sistemas de arquivos em que os blocos de um arquivo são alocados de forma contígua na mídia de armazenamento físico. Isso significa que os blocos são atribuídos em sequência, um após o outro, ocupando posições físicas consecutivas.

Esse método é relativamente simples de ser implementado e requer pouca informação adicional para cada arquivo. A leitura de um arquivo alocado de forma contínua é eficiente, pois basta um único seek para acessar todo o arquivo em sequência.

#### Problema

No entanto, a alocação contínua apresenta alguns problemas. Um deles é a fragmentação (externa). Conforme os arquivos são criados, alterados e removidos, ocorre fragmentação do espaço livre no sistema de arquivos. Isso significa que blocos livres podem ficar espalhados ao redor do disco, o que dificulta a alocação contígua de novos arquivos e pode levar ao desperdício de espaço.

Outro problema é que a alocação contínua requer o conhecimento do tamanho do arquivo no momento da criação. Se um arquivo precisar ser aumentado posteriormente, pode ser necessário realocar o arquivo inteiro em uma nova região contígua do disco, o que pode ser um processo demorado e com alto overhead.

#### Uso anteriormente

A alocação contínua foi amplamente usada em sistemas de arquivos para fitas magnéticas, onde o acesso sequencial era comum.  No entanto, com o surgimento de mídias de armazenamento mais rápidas e flexíveis, como discos rígidos e SSDs, a alocação contínua caiu em desuso devido aos problemas de fragmentação e restrições de tamanho dos arquivos.

No entanto, em certos casos, como em CD-ROMs, DVDs ou discos Blu-ray, a alocação contínua ainda pode ser utilizada devido à natureza sequencial dessas mídias, em que a leitura é realizada em uma única passagem.

### Alocação de arquivos em lista ligada 

#### O que é?

A alocação de arquivos em lista ligada é um método de implementação de sistemas de arquivos em que cada bloco de um arquivo contém um ponteiro para o endereço no disco do próximo bloco do arquivo. Dessa forma, os blocos de um arquivo são encadeados através desses ponteiros, formando uma lista ligada.

#### Vantagens

##### Elimina o problema de fragmentação externa

Uma vantagem da alocação em lista ligada é que ela elimina o problema de fragmentação externa. Como os blocos não precisam ser alocados de forma contígua, não ocorre fragmentação do espaço livre no sistema de arquivos. Isso permite que os arquivos sejam alocados de maneira flexível, utilizando apenas os blocos necessários, independentemente de sua localização física.

##### Acesso sequencial

Essa forma de alocação é especialmente eficiente para acesso sequencial, pois a leitura ou gravação de um arquivo pode ser realizada em sequência, seguindo os ponteiros da lista ligada.

#### Desvantagens

##### Acesso aleatório

Péssima performance em acesso aleatório. Para acessar um bloco específico em um arquivo, é necessário percorrer toda a lista ligada a partir do início do arquivo até o bloco desejado. Isso pode resultar em um tempo de acesso considerável, especialmente para arquivos grandes.

##### Fragmentação interna

Outra desvantagem é a fragmentação interna. Como cada bloco precisa armazenar um ponteiro para o próximo bloco, há um espaço adicional ocupado pelos ponteiros nos blocos. Isso pode levar a um desperdício de espaço, pois o tamanho dos blocos não é mais uma potência de 2, dificultando a relação entre bloco e setor no disco.

### Tabela (FAT) 

A implementação de sistemas de arquivos utilizando uma tabela (File Allocation Table - FAT) é um método amplamente utilizado em sistemas operacionais.

#### O que é?

 Nesse método, alguns blocos do disco são reservados para armazenar uma tabela que contém informações sobre a alocação dos blocos de arquivos no sistema de arquivos.

 Cada entrada na tabela FAT corresponde a um bloco na partição do disco. Essas entradas são utilizadas para indicar o próximo bloco de um arquivo. A entrada no diretório de um arquivo contém o número do primeiro bloco desse arquivo na tabela FAT.

#### Vantagens

##### Simpliciade e eficiência

Uma das principais vantagens da tabela FAT é a sua simplicidade. A tabela é carregada na memória durante a inicialização do sistema de arquivos, o que permite um acesso rápido e eficiente às informações de alocação.

##### Acesso aleatório

Isso torna o acesso aleatório a arquivos relativamente rápido, já que a localização dos blocos é diretamente obtida a partir da tabela residente na memória.

#### Desvantagens

##### Tamanho

No entanto, a implementação da tabela FAT também apresenta algumas limitações. Uma delas é o problema relacionado aos tamanhos. Existem diferentes versões da tabela FAT, como FAT-12, FAT-16 e FAT-32, que possuem limites diferentes para o número máximo de blocos suportados. Por exemplo, o sistema FAT-32 tem um limite de aproximadamente 4 bilhões de blocos.

##### Fragmentação interna

Além disso, a tabela FAT pode levar a um desperdício de espaço em disco, especialmente para arquivos pequenos. Isso ocorre devido à alocação em blocos fixos, onde um arquivo pode ocupar um bloco inteiro, mesmo que seja menor do que o tamanho do bloco.

![image](https://github.com/sabrizzs/hello-world/assets/93349105/ce15efad-5f5b-4486-b289-076c3cdeaaaf)


### I-Nodes

A implementação de sistemas de arquivos utilizando I-Nodes é comumente encontrada em sistemas Unix. 

#### O que é?

 Nesse método, cada arquivo é associado a um registro chamado I-Node (índice do nó-i), que contém informações e ponteiros para os blocos de dados do arquivo.

 O I-Node armazena informações sobre o arquivo, como permissões, proprietário, tamanho, timestamps (data e hora de criação, acesso e modificação), entre outros atributos. 

#### Ponteiros

Ele contém ponteiros para os primeiros blocos de dados do arquivo. Esses ponteiros podem ser diretos, quando apontam diretamente para os blocos de dados, ou indiretos, quando apontam para outras estruturas que, por sua vez, apontam para os blocos de dados.

Para arquivos maiores, o esquema de acesso indireto é utilizado. Existem três níveis de acesso indireto: single indirect, double indirect e triple indirect, que permitem o acesso a um número maior de blocos de dados.

![image](https://github.com/sabrizzs/hello-world/assets/93349105/d49d7639-13bc-4b8a-bc19-8c000b05f9b4)

#### Arquivos pequenos

Uma das principais vantagens do uso de i-nodes é o baixo overhead para arquivos pequenos. Como as informações e ponteiros são armazenados no i-node, o espaço ocupado pelos metadados é relativamente pequeno em comparação com o tamanho do arquivo.

#### Arquivos grandes

O acesso a arquivos grandes de forma totalmente aleatória pode ser lento devido à necessidade de leituras adicionais do disco para acessar os blocos de dados indiretos. No entanto, esse problema é mitigado pelo princípio da localidade, que sugere que os arquivos tendem a ser acessados em regiões próximas do disco, o que reduz a latência.

#### Escalável

Outra vantagem do uso de i-nodes é a escalabilidade no tamanho do arquivo. Com o uso de 32 bits para endereçamento, é possível endereçar um número muito grande de blocos. Por exemplo, com blocos de 4 KB, um disco de 16 TB pode acomodar um arquivo de até 4 TB. Com blocos de 8 KB, um disco de 32 TB pode acomodar um arquivo de até 32 TB.

## Implementação de diretórios

### CP/M

A implementação de diretórios no sistema CP/M é específica para computadores de 8 bits. Nesse sistema, existe apenas um diretório que contém todas as entradas de arquivos.

Cada entrada de arquivo possui um tamanho padrão e é composta pelos seguintes campos:

- Código do usuário (1 byte): Identifica o usuário proprietário do arquivo.
- Nome (8 bytes): O nome do arquivo, limitado a 8 caracteres.
- Extensão (3 bytes): A extensão do arquivo, limitada a 3 caracteres.
- Extent (1 byte): Utilizado para arquivos que possuem mais de uma entrada, indicando o número da entrada correspondente.
- Livre (2 bytes): Espaço livre disponível para o arquivo.
- Blocos em uso (1 byte): Indica quantos blocos de dados estão sendo usados pelo arquivo.
- Apontadores para disco (16 bytes): Ponteiros que apontam para os blocos de dados do arquivo no disco.
- Arquivos grandes repetem entradas: Para arquivos grandes, que não podem ser representados completamente em uma única entrada, são usadas múltiplas entradas repetindo os campos acima.

### DOS (precursor do Windows) 

A implementação de diretórios no sistema DOS (precursor do Windows) é utilizada em sistemas de 16 bits e foi originalmente projetada para discos de 10MB. 

Nesse sistema, o diretório raiz é fixo e possui 112 entradas para floppies (discos flexíveis).

Além do diretório raiz, outros diretórios são tratados como arquivos normais e também podem conter entradas de diretório.

O DOS utiliza uma estrutura hierárquica de diretórios, permitindo a criação de subdiretórios dentro do diretório raiz. 

No entanto, ao contrário de sistemas mais modernos, como o Unix, o DOS não possui suporte para atributos de usuário nos diretórios.

Cada entrada de arquivo no diretório possui um tamanho padrão e é composta pelos seguintes campos:

- Nome (8 bytes): O nome do arquivo, limitado a 8 caracteres.
- Extensão (3 bytes): A extensão do arquivo, limitada a 3 caracteres.
- Atributos (1 byte): Indica os atributos do arquivo, como somente leitura, oculto, sistema, diretório, etc.
- Livre (2x2 bytes): Espaço livre disponível para o arquivo.
- Primeiro bloco na FAT (2 bytes): O número do primeiro bloco do arquivo na tabela de alocação de arquivos (FAT - File Allocation Table).
- Tamanho (4 bytes): O tamanho do arquivo em bytes.

### Windows 95

Existem dois tipos de entrada de diretório utilizados para garantir compatibilidade com sistemas anteriores.

No Windows 95, a estrutura básica de uma entrada de diretório tem o seguinte formato:

- Nome (8 bytes): O nome do arquivo ou diretório, limitado a 8 caracteres.
- Extensão (3 bytes): A extensão do arquivo, limitada a 3 caracteres.
- Atributos (1 byte): Indica os atributos do arquivo, como somente leitura, oculto, arquivo de sistema, etc.
- Campo NT (1 byte): Utilizado para suportar recursos adicionais do sistema operacional Windows NT.
- Sec (1 byte): O número do setor onde a entrada de diretório está localizada.
- Data e horário da criação (4 bytes): Indica a data e o horário em que o arquivo foi criado.
- Último acesso (2 bytes): Indica a data do último acesso ao arquivo.
- 16 bits superiores do primeiro bloco (2 bytes): Indica a parte mais significativa do número do primeiro bloco de dados do arquivo.
- Data e horário da última escrita (4 bytes): Indica a data e o horário da última modificação do arquivo.
- 16 bits inferiores do primeiro bloco (2 bytes): Indica a parte menos significativa do número do primeiro bloco de dados do arquivo.
- Tamanho (4 bytes): O tamanho do arquivo em bytes.

Além da entrada básica, o Windows 95 também introduziu a possibilidade de ter entradas adicionais para suportar nomes de arquivos grandes. 

Essas entradas adicionais estão associadas ao mesmo arquivo e têm o seguinte formato:

- Sequência (1 byte): Indica a sequência da entrada adicional para o mesmo arquivo.
- 5 caracteres (10 bytes): Parte do nome do arquivo que não cabe na entrada básica.
- Atributo (1 byte): Atributo do arquivo. Um valor inválido para o DOS não compromete a busca.
- Zero (1 byte): Byte zero para fins de preenchimento.
- Checksum (1 byte): Um byte de verificação de integridade.
- 6 caracteres (12 bytes): Parte restante do nome do arquivo.
- Zero (2 bytes): Dois bytes zero para fins de preenchimento.
- Dois caracteres (4 bytes): Caracteres extras para completar o nome do arquivo.

### Unix 

A implementação de diretórios no Unix utiliza uma tabela de I-nodes (índices de nós-i) para armazenar informações sobre os arquivos e diretórios em uma partição. 

Essa tabela está localizada em um local fixo na partição, geralmente referido como "superbloco".

A localização de um I-node a partir do seu número é facilmente obtida devido à sua estrutura fixa.

#### Diretório

No Unix, os diretórios são tratados como arquivos normais. Cada diretório tem um I-node associado, e as entradas dentro do diretório contêm o número do I-node correspondente e o nome do arquivo/diretório.

A entrada de diretório no Unix possui o seguinte formato:

- Número do I-node (2 bytes): Um valor que identifica o I-node associado ao arquivo ou diretório.
- Nome (14 bytes): O nome do arquivo ou diretório.

O formato exato da entrada pode variar dependendo da implementação do sistema Unix, mas a combinação de I-node e nome é sempre presente.

#### Busca de arquivo

A busca por um arquivo ou diretório em um sistema Unix segue um processo recursivo. Começando com o I-node do diretório raiz, o sistema carrega o diretório e busca pelo nome do arquivo ou diretório desejado. Em cada passo do caminho, o sistema obtém o número do I-node correspondente à entrada atual e repete o processo até encontrar o arquivo ou diretório desejado.

### NTFS (Windows 2000 e depois) 

A implementação de diretórios no NTFS (New Technology File System), usado no Windows 2000 e versões posteriores, difere do conceito tradicional de arquivos como um conjunto de bytes. No NTFS, um arquivo é composto por um conjunto de atributos, sendo cada atributo um fluxo de bytes que armazena informações específicas sobre o arquivo.

A estrutura básica para armazenar e gerenciar arquivos no NTFS é chamada de Master File Table (MFT), que é um arquivo especial no sistema de arquivos. O MFT contém informações sobre todos os arquivos e diretórios presentes na partição formatada com NTFS.

A MFT contém até 16 atributos para cada arquivo, sendo que cada atributo pode ter um tamanho máximo de 1 kb.

Uma característica interessante do NTFS é que alguns atributos podem ser não residentes, ou seja, podem apontar para outros arquivos que contêm mais atributos. 

## Administração de espaço

A administração de espaço em disco é uma questão importante nos sistemas de arquivos. Existem duas abordagens principais para gerenciar o espaço em disco: 

- sequência contígua de bytes:  os arquivos são armazenados como uma sequência contínua de bytes no disco.
- sequência de blocos: os arquivos são divididos em blocos de tamanho fixo.

### Tamanho do bloco

O tamanho do bloco é um aspecto importante na administração de espaço. Os candidatos comuns para o tamanho do bloco são setor, trilha e cilindro. A escolha do tamanho do bloco envolve um trade-off entre desperdício de espaço e taxa de transferência de dados. Blocos maiores podem reduzir o desperdício de espaço, mas podem resultar em transferências de dados mais lentas, pois podem ser necessárias leituras/gravações de blocos inteiros, mesmo que apenas uma pequena parte seja necessária.

### Tamanho dos arquivos 

O tamanho dos arquivos também influencia a administração de espaço. Diferentes sistemas operacionais e aplicativos têm tamanhos de arquivo medianos diferentes. Por exemplo, no Unix, a mediana do tamanho dos programas é de cerca de 2 KB, enquanto em sistemas Windows em ambientes científicos, como na Universidade de Cornell, também é em torno de 2 KB. 

### Espaço livre 

 Existem duas abordagens comuns para gerenciar o espaço livre: lista ligada de blocos livres e vetor de bits.

 #### Lista ligada de blocos livres
 
 Na abordagem da lista ligada de blocos livres, os blocos livres são organizados em uma lista ligada, onde cada bloco livre contém um ponteiro para o próximo bloco livre na lista.

 A implementação dessa abordagem é relativamente simples, pois apenas um bloco da lista precisa estar na memória de cada vez. 

#### Vetor de bits

 Na abordagem do vetor de bits, cada bloco do disco é representado por um bit no vetor. Se um bit estiver definido como 0, isso indica que o bloco está livre; se estiver definido como 1, indica que o bloco está em uso. 

  Essa abordagem é muito compacta, requerendo apenas 1 bit por bloco, o que resulta em um vetor de bits de tamanho fixo. 

  Por exemplo, um bloco de 1 KB pode conter a indexação de 8 mil blocos (8 MB). Portanto, um disco de 8 TB pode ser indexado com apenas 125 MB de vetor de bits. 
  
  No entanto, a implementação da busca de blocos livres pode ser mais complexa nessa abordagem, uma vez que é necessário pesquisar o vetor de bits para encontrar blocos livres contíguos.

## Compartilhamento de arquivos

Quando vários usuários desejam compartilhar um arquivo, é conveniente que esse arquivo possa ser acessado simultaneamente em diferentes diretórios.

Essa estrutura de diretórios, em que um arquivo pode ter múltiplas conexões, é conhecida como um grafo acíclico direcionado (DAG), em oposição à estrutura de árvore tradicional.

Existem duas maneiras principais de criar essas novas conexões, ou links, entre diretórios e arquivos: hard links (links físicos) e symbolic links (links simbólicos).

### Hard links

Os hard links são implementados fazendo com que várias entradas de diretório compartilhem o mesmo descritor de arquivo. Isso significa que várias entradas de diretório apontam para o mesmo arquivo físico no sistema de arquivos, e a lista de blocos que compõem o arquivo não é duplicada nas entradas do diretório. 

Os hard links são amplamente utilizados em sistemas UNIX.

### Links simbólicos

Os symbolic links, por sua vez, são arquivos especiais que contêm o caminho para a localização real do arquivo.

### Problemas

Ao compartilhar arquivos através de links, independentemente se são links simbólicos ou hard links, podem surgir alguns problemas que precisam ser considerados:

#### Hard links:

- Remoção de arquivo: Ao remover um arquivo que possui hard links, é necessário garantir que o arquivo real só seja excluído quando não houver mais links apontando para ele. Isso é controlado pelo contador de links no inode do arquivo. É importante ter cuidado ao remover arquivos com hard links para evitar a perda acidental de dados.
  
- Cobrança de espaço: No caso dos hard links, o espaço ocupado pelo arquivo é contabilizado uma vez para cada link. Portanto, mesmo que outros usuários tenham links para o arquivo, o usuário original continuará sendo cobrado pelo espaço total ocupado.
  
- Arquivo removido pelo dono continua sendo usado: Se um arquivo for removido pelo proprietário, mas outros usuários ainda tiverem links para o arquivo, ele ainda poderá ser acessado e usado. Isso pode levar a situações em que o arquivo é aparentemente removido, mas ainda está em uso.
  
- Ciclos: É possível criar ciclos de hard links, onde um arquivo é linkado a si mesmo ou a outros arquivos em uma cadeia circular. Isso pode levar a problemas de recursão infinita e dificuldades na navegação e gerenciamento dos arquivos.

#### Links simbólicos:

- Sobrecarga de acesso: Ao abrir um arquivo através de um symbolic link, há uma pequena sobrecarga de acesso, pois o sistema precisa seguir o caminho indicado pelo link para encontrar o arquivo real. Essa sobrecarga ocorre apenas durante a abertura do arquivo.

- Entradas órfãs de arquivos eliminados: Se um arquivo referenciado por um symbolic link for removido, o link se torna órfão e não pode mais acessar o arquivo. Isso pode resultar em entradas de diretório inválidas ou links quebrados.

#### Problemas gerais:

- Backups: Ao fazer backups de sistemas de arquivos com links, é necessário tomar cuidado para evitar a duplicação de trabalho. Os backups devem ser capazes de lidar corretamente com os links e garantir que os arquivos compartilhados não sejam duplicados desnecessariamente.
  
- Reconstituição e unicidade: Em situações de restauração de backups ou reconstituição do sistema de arquivos, é essencial garantir a unicidade dos arquivos. Os links devem ser restaurados corretamente para manter a estrutura de compartilhamento de arquivos intacta.

## Confiabilidade do sistema de arquivos

A confiabilidade do sistema de arquivos é uma preocupação fundamental, pois os arquivos armazenados são frequentemente mais valiosos do que o próprio hardware. Existem várias estratégias para garantir a confiabilidade do sistema de arquivos, incluindo:

### Localização dos setores ruins do disco:

- No nível de hardware, um setor do disco pode conter uma lista dos blocos ruins, juntamente com os blocos substitutos disponíveis. O controlador do disco pode usar automaticamente os blocos substitutos ao acessar os setores defeituosos, garantindo a integridade dos dados. Isso permite que o sistema de arquivos evite áreas danificadas do disco e continue a operar normalmente.
- No nível de software, o sistema de arquivos pode construir um arquivo especial que contém informações sobre os blocos ruins do disco. Essas informações são utilizadas para evitar a alocação de blocos defeituosos e garantir que os dados sejam armazenados em áreas saudáveis do disco.

### Atualização atômica:

- A atualização atômica é um conceito importante para manter a consistência dos arquivos no sistema de arquivos. Isso significa que as operações de atualização devem ser tratadas como uma unidade indivisível, de modo que, se uma atualização falhar antes de ser concluída, o sistema possa garantir que os arquivos permaneçam consistentes.
- Se uma atualização falhar, basta executar novamente a operação para garantir que os arquivos sejam atualizados corretamente. Isso evita a corrupção de dados e mantém a integridade dos arquivos no sistema de arquivos.
- Discos com atualização atômica tolerante a falhas: Para garantir a tolerância a falhas e melhorar a confiabilidade, é possível implementar discos com atualização atômica. Isso envolve o uso de múltiplos discos físicos em um arranjo lógico, onde as operações de atualização são executadas de forma atômica em todos os discos simultaneamente. 

### RAID

RAID (Redundant Array of Independent Disks) é um esquema que permite a operação de vários discos como se fossem apenas um, criando um "disco virtual". O RAID oferece benefícios em termos de capacidade, desempenho e confiabilidade. Existem vários níveis de RAID, cada um com suas próprias características. 

#### RAID 0

Nesse nível, dois ou mais discos são combinados para criar um único disco maior. Não há redundância de dados ou recursos de recuperação. O principal objetivo é aumentar a capacidade do sistema de arquivos e melhorar a velocidade de leitura e gravação. No entanto, não há proteção contra falhas de disco, ou seja, se um disco falhar, todos os dados serão perdidos.

#### RAID 1

No RAID 1, os discos são espelhados, o que significa que os dados são gravados em dois ou mais discos simultaneamente. Em caso de falha de um disco, os dados podem ser recuperados a partir da cópia espelhada. Isso fornece uma recuperação simples para falhas de disco, mas também resulta em uma leitura mais rápida, já que os dados podem ser lidos a partir de qualquer um dos discos espelhados.

#### RAID 5

O RAID 5 utiliza uma técnica chamada "stripping" de blocos com paridade distribuída. Os dados e a paridade são distribuídos entre os discos. Se um disco falhar, os dados podem ser recuperados usando os blocos restantes e a paridade. O RAID 5 oferece tolerância a falhas, pois pode resistir à falha de qualquer disco (desde que haja um mínimo de três discos). O desempenho de leitura e gravação é geralmente melhorado em comparação com um único disco, mas o desempenho com uma falha é reduzido.

#### RAID 6

O RAID 6 é semelhante ao RAID 5, mas usa paridade dupla distribuída. Isso significa que até duas falhas de disco podem ser toleradas. Assim como o RAID 5, o RAID 6 oferece melhor desempenho de leitura e gravação em comparação com um único disco, mas o desempenho com falhas é reduzido.

#### Outras RAIDS

Existem outros níveis de RAID, como RAID 2 e RAID 3, que utilizam técnicas de bit stripping e byte stripping, respectivamente. Também existem arranjos RAID compostos, conhecidos como RAID "nested", como o RAID 10, que combina os benefícios de diferentes níveis de RAID.



