---
title: "Erro no postinstall intercept hook"
date: '2025-03-09T00:10:32-03:00'
# weight: 1
# aliases: ["/first"]
categorias: ["Yocto", "Linux"]
tags: ["Permission"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "postinstall intercept hook 'update_desktop_database' error"
disableHLJS: true # to disable highlightjs
disableShare: false
disableHLJS: false
hideSummary: false
searchHidden: false
ShowReadingTime: true
ShowBreadCrumbs: true
ShowPostNavLinks: true
ShowWordCount: true
ShowRssButtonInSectionTermList: true
UseHugoToc: true
cover:
    image: images/yocto/no-access.jpg # image path/url
    alt: "Foto de Michael Nunzio." # alt text
    caption: "fonte: https://www.pexels.com/pt-br/foto/perigo-risco-sinal-de-aviso-sinal-de-alerta-4189458/" # display caption under cover
    relative: false # when using page bundles set this to true
    hidden: false # only hide on current single page
    hiddenInSingle: false
    responsiveImages: true
editPost:
    URL: "https://github.com/danieltak/danieltak-blog/blob/master/content"
    Text: "Sugerir Alterações" # edit text
    appendFilePath: true # to append file path to Edit link
---

## Introdução

Ao gerar o yocto manualmente, não tinha problemas.

Porém, após criar uma pipeline para gerar imagens de forma automatizada durante o processo de desenvolvimento, o seguinte erro apareceu:

> update_desktop_database: 7: update-desktop-database: not found

Ou

> update_desktop_database: 7: update-desktop-database: command not found

A solução mais fácil é comentar os scripts de verificação, mas após algum tempo fui pesquisar mais a fundo e segue a resposta para este erro.

## Solução

### update-desktop-database

Primeiro o pacote [update-desktop-database] não estava instalado na máquina e era necessário.

Portanto, você deve instalar o pacote se ele não estiver instalado no seu sistema operacional, caso contrário, o comando não será encontrado.

Um passo para verificar e instalar o pacote [extra/desktop-file-utils] foi adicionado à pipeline.

### Permissão

Após instalar o pacote, o problema persistiu...

O problema é a permissão dos arquivos de post install. Na pipeline de ci-cd, após clonar o repositório com os arquivos para gerar a imagem yocto, a permissão e o dono de todos os arquivos era alterada. Permissão `755` e dono `gitlab-runner`.

Verifique as permissões dos arquivos do diretório `poky/scripts/postinst-intercepts`.

Normalmente, o `postinst_intercept` deve possuir a permissão `755` ou `-rwxr-xr-x`. E todos os outros arquivos `644` ou `-rw-rw-r--`.

## Referências

[Yocto: postinstall intercept hook "update_desktop_database" error]: https://stackoverflow.com/questions/70841836/yocto-postinstall-intercept-hook-update-desktop-database-error

- [Yocto: postinstall intercept hook "update_desktop_database" error]

[update-desktop-database]: https://man.archlinux.org/man/update-desktop-database.1.en

- [update-desktop-database]

[extra/desktop-file-utils]: https://www.archlinux.org/packages/extra/x86_64/desktop-file-utils/

- [extra/desktop-file-utils]