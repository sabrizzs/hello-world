## CVE-2023-22499

- exploit e patch no github
- Por exemplo, imagine que um programa malicioso está executando várias tarefas em paralelo e precisa de permissão do usuário para acessar um arquivo. Em vez de solicitar permissão de forma clara e honesta, o programa malicioso poderia mostrar uma mensagem de permissão que parece estar pedindo permissão para uma ação inofensiva, como "Visualizar um gráfico". Depois de obter a permissão do usuário, o programa poderia limpar a tela do terminal (a interface de linha de comando) para esconder a verdadeira ação que está sendo executada.
- nao sei se tem o codigo do exploit

Deno is a runtime for JavaScript and TypeScript that uses V8 and is built in Rust. Multi-threaded programs were able to spoof interactive permission prompt by rewriting the prompt to suggest that program is waiting on user confirmation to unrelated action. A malicious program could clear the terminal screen after permission prompt was shown and write a generic message. This situation impacts users who use Web Worker API and relied on interactive permission prompt. The reproduction is very timing sensitive and can’t be reliably reproduced on every try. This problem can not be exploited on systems that do not attach an interactive prompt (for example headless servers). The problem has been fixed in Deno v1.29.3; it is recommended all users update to this version. Users are advised to upgrade. Users unable to upgrade may run with --no-prompt flag to disable interactive permission prompts.

## CVE-2023-41887

- exploit e patch no github
- permitia que qualquer usuário não autenticado executasse código no servidor onde o OpenRefine estava instalado.

OpenRefine is a powerful free, open source tool for working with messy data. Prior to version 3.7.5, a remote code execution vulnerability allows any unauthenticated user to execute code on the server. Version 3.7.5 has a patch for this issue.

## CVE-2023-40028

- patch(com exploit como teste unitario) no github
- a vulnerabilidade no Ghost permitia que usuários autenticados fizessem upload de symlinks que apontassem para arquivos no sistema operacional do host. 
- isso poderia ser explorado para a leitura arbitrária de arquivos no sistema.

Ghost is an open source content management system. Versions prior to 5.59.1 are subject to a vulnerability which allows authenticated users to upload files that are symlinks. This can be exploited to perform an arbitrary file read of any file on the host operating system. Site administrators can check for exploitation of this issue by looking for unknown symlinks within Ghost's `content/` folder. Version 5.59.1 contains a fix for this issue. All users are advised to upgrade. There are no known workarounds for this vulnerability.

## CVE-2023-43804 

- exploit e patch note de python url3lib
- a vulnerabilidade ocorria quando um usuário especificava explicitamente um cabeçalho Cookie em suas solicitações HTTP, mas não desabilitava os redirecionamentos HTTP explicitamente.
- isso poderia resultar no vazamento não intencional de informações confidenciais ou de autenticação para um servidor não autorizado.
- só achei o patch

urllib3 is a user-friendly HTTP client library for Python. urllib3 doesn't treat the `Cookie` HTTP header special or provide any helpers for managing cookies over HTTP, that is the responsibility of the user. However, it is possible for a user to specify a `Cookie` header and unknowingly leak information via HTTP redirects to a different origin if that user doesn't disable redirects explicitly. This issue has been patched in urllib3 version 1.26.17 or 2.0.5.

## CVE-2023-40581

- yt-dlp
- exploit e patch no github
- era possível executar código remotamente no computador do usuário, mas apenas no caso específico de o usuário usar a opção --exec com dados maliciosamente criados.

yt-dlp is a youtube-dl fork with additional features and fixes. yt-dlp allows the user to provide shell command lines to be executed at various stages in its download steps through the `--exec` flag. This flag allows output template expansion in its argument, so that metadata values may be used in the shell commands. The metadata fields can be combined with the `%q` conversion, which is intended to quote/escape these values so they can be safely passed to the shell. However, the escaping used for `cmd` (the shell used by Python's `subprocess` on Windows) does not properly escape special characters, which can allow for remote code execution if `--exec` is used directly with maliciously crafted remote data. This vulnerability only impacts `yt-dlp` on Windows, and the vulnerability is present regardless of whether `yt-dlp` is run from `cmd` or from `PowerShell`. Support for output template expansion in `--exec`, along with this vulnerable behavior, was added to `yt-dlp` in version 2021.04.11. yt-dlp version 2023.09.24 fixes this issue by properly escaping each special character. `\n` will be replaced by `\r` as no way of escaping it has been found. It is recommended to upgrade yt-dlp to version 2023.09.24 as soon as possible. Also, always be careful when using --exec, because while this specific vulnerability has been patched, using unvalidated input in shell commands is inherently dangerous. For Windows users who are not able to upgrade: 1. Avoid using any output template expansion in --exec other than {} (filepath). 2. If expansion in --exec is needed, verify the fields you are using do not contain ", | or &. 3. Instead of using --exec, write the info json and load the fields from it instead.