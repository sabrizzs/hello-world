# PF

parei: 234

slides: 1 - 229 - 259 ; 380 - 403 (ao todo cerca de 60 slides)

respostas das provas: https://docs.google.com/document/d/1htvzhlW3EPrYwOh2mBsPRAcDP2JfZFJfiu5Z6QvfnTY/edit?pli=1

## Confiabilidade do sistema de arquivos

- Controle de concorrência
    - Unix: leitura e escrita executadas na ordem em que chegam
    - Problema quando precisa de exclusão mútua
    - Solução mais comum: "locks" (1 por arquivo)
    - Mesmo problema que exclusão mútua, se usuário "pifar" trava o arquivo
    - Nesse caso tem ênfase nos dados, a prioridade é manter os arquivos sem que sejam corrompidos ou perdidos

- Transações
    - Transação: unidade lógica que agrupa operações
    - begin_transaction
    - as operações são executadas normalmente com travas nos recursos
    - porém as alterações só são aplicadas com end_transaction
    - evita problemas quando há falhas e erros, e ajuda a reverter alterações nesses erros

- Cópias de segurança (backups)
    - Recuperação de desastres e erros
    - Lento e alto uso de espaço
    - O que recuperar com o backup? Dump Físico ou Dump Lógico?
    - Dump: cópia ou salvamento de dados para o local de backup

    - Dump Físico
        - Copia o disco inteiro, blocos e setores, bit a bit
        - Simples, mas custoso em tempo e armazenamento
        - Blocos inválidos
            - desperdício de espaço, erros
            - se mantidos pelo hardware ok, pois o próprio hardware está lidando com esse bloco
            - se mantidos pelo SO (sabe quais são os blocos), backup deve saber também e evitar copiá-los
        
    - Dump Lógico
        - Não copia arquivos especiais ((comunicação)pipes,/dev/,etc), executaveis, temporários
        - Copia diretórios específicos e recursivamente seus arquivos

    - Dumps incrementais
        - evita novo backup de arquivos não mudados
        - periodicamente um dump completo e incrementais são feitos
        - mas há uma certa complexidade na recuperação, pois é necessário salvar diretórios não modificados para facilitar a recuperação

    - Unix pode ter "buracos" nos arquivos
        - por causa de operaçoes como a sequencia open, write, seek (deslocamento), write
        - não preencher buracos na recuperação
        - core dump: arquivo sobre a memoria de um programa quando ocorre uma falha, possuem espaço entre código e pilha que nao contem informações relevantes sobre a falha

    - Cuidado com links para evitar duplicação e loops
        - hard links, soft links

## Consistência do sistema de arquivos

## Performance do sistema de arquivos

## Sistemas de arquivos estruturados como logs

## Segurança

## Threads
