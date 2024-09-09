---
title: "Escolha do Sistema Operacional"
date: '2024-03-15T20:11:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Windows", "Linux", "Sistema Operacional"]
categorias: ["Choices", "Opinião"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Alguns argumentos sobre cada sistema operacional e a razão de eu escolher este sistema."
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
    image: images/operating-system/Operating-system.png # image path/url
    alt: "Aguzer, CC0, via Wikimedia Commons" # alt text
    caption: "fonte: https://commons.wikimedia.org/wiki/File:Operating-system.svg" # display caption under cover
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

Quando se trata de Sistema Operacional (SO) para desktop, como engenheiro e funcionário do mundo corporativo, a escolha sempre foi o Windows, pela compatibilidade com os softwares utilizados e o controle da TI. Mas para programação, o Linux pode ser uma alternativa em muitos casos, mas em empresas o Departamento de TI normalmente liberará somente o Windows.

Já para servidores este cenário é um pouco diferente...

Pois para desenvolvimento, necessitamos dos últimos pacotes ou de muitos drivers. Já para ambiente de produção, o principal é a robustes e alta disponibilidade. Os pacotes de desenvolvimento normalmente não estão instalados nos servidores ou demoram para serem atualizados.

Na maioria dos casos de desenvolvimento um Windows com virtualização do Linux atende as necessidades, em outros um dual boot com Windows e Linux é necessário. Porém, eu tive mais problemas do que soluções com o dual boot, quem já usou o dual boot sabe que o Windows Updater acaba desconfigurando o boot loader (GRUB).

Para atividades diretamente ligadas ao Hardware ou com otimizações da GPU, creio que o acesso direto ao hardware, sem virtualização, é importante.

**Então qual sistema operacional eu devo usar?**

A resposta sempre é, depende.

## Linux vs Windows para Servidores

Como usuário de Open Source e que não gostaria de gastar muito dinheiro com licenças, a opção de Linux é óbvia.

Mas vamos analisar um pouco as vantagens do Windows. Possui suporte e hotline, amplamente utilizado, com muitos profissionais para prestar serviço de suporte, muitos dos softwares pagos e validados em corporações possuem maior compatibilidade com Windows. Ou seja, é um ganha pão melhor para possuir clientes ou um trabalho. 

**A maioria das vezes a escolha deste SO é pela transferência responsabilidade para a prestadora de serviços e não se preocupar com o SO**, que é algo complexo e muitas vezes não é necessário uma equipe ou colaborador para prestar suporte ao SO.

Uma grande desvantagem que presenciei na vida profissional, muitos detalhes são extremamente específicos do Windows e há pouca informação sobre estes detalhes mais incomuns. Um "dinossauro" da área foi consultado ($$) e muitos problemas foram resolvidos, porém estas informações não estavam documentadas ou facilmente encontradas.

Para uma empresa corporativa, em que é necessário um Windows Server para gerenciar os usuários, e-mails e policies. Como administrador do sistema, o Windows Server seria a melhor opção e o custo adicional não seria o problema para uma empresa grande.

A escolha para alguém que não possui muito dinheiro seria o Linux, correto? Sim, mas qual das distribuições?

### Distribuição Linux

RHEL (Red Hat) é pago e a fundação terminou o projeto de desenvolvimento do CentOS ( Open source ) em 2020. Por vários motivos, mas esse era a alternativa mais utilizada do mercado. 

Recentemente compraram o Fedora e muitos cogitam a possibilidade do Red Hat Foundation matar este SO também.

Pelo que pesquisei as mais utilizadas recentemente são Ubuntu Server e Debian.

### Debian vs Ubuntu

O Ubuntu é um fork do Debian que está na versão mais instável, porém é mais atualizado e possui funcionalidades mais novas. Recomendado para o usuário que trabalha com pesquisas ou projetos ultra modernos e necessita de recursos mais recentes, inclusive drivers para hardwares que lançaram recentemente.

Já o Debian lança um release estável com mais tempo e testes, portanto, alguns recursos são desatualizados, por outro lado, é muito mais estável.

Como meu foco é possuir um servidor estável, com utilização de recursos estáveis e testados, que não me dê problemas e com um Hardware mais barato. A escolha do Debian ficou fácil.

Mas instalar um servidor com GUI? Se sim, qual a escolha do ambiente gráfico?

Debian e Ubuntu são duas distribuições Linux populares usadas como sistemas operacionais de desktop e servidor. Ambas são distros de código aberto com excelente reputação e bases de usuários consideráveis. No entanto, existem algumas diferenças entre os dois que tornam um ou outro mais adequado para determinados casos de uso.

O Debian está entre as distribuições Linux mais antigas e confiáveis ​​do mercado. É a escolha certa para ambientes que priorizam a estabilidade e a segurança do sistema, como servidores de produção. O suporte e a confiabilidade de longo prazo do Debian fazem dele uma opção preferida para servidores que exigem operação ininterrupta e sem surpresas. A equipe de segurança do Debian tem um histórico comprovado de patches de segurança eficazes e oportunos. O gerenciador de pacotes do Debian (Advanced Package Tool, ou APT, abreviadamente) simplifica as instalações e atualizações de software. O Debian é um projeto conduzido pela comunidade, portanto não há nenhuma entidade comercial por trás desta distribuição Linux.

O Ubuntu, por outro lado, é uma distribuição mais amigável e versátil, mais adequada para uso em desktop. É baseado no Debian e compartilha muitos de seus recursos, mas tem um ciclo de lançamento mais rápido e é mais avançado. Ubuntu é uma boa escolha para servidores que exigem os recursos e atualizações de software mais recentes. Ele também possui uma base de usuários maior e mais opções de suporte comercial que o Debian.

Em resumo, se você prioriza estabilidade e segurança em vez de novos recursos e atualizações de software, o Debian é a melhor escolha para o seu servidor. Se você deseja uma distribuição mais amigável e versátil, mais adequada para uso em desktop, o Ubuntu é a escolha certa.

### KDE vs GNOME

O GNOME possui um design moderno e diferente, porém menos ferramentas. Por ser utilizado no Ubuntu, creio que seja muito robusto e com atualizações mais rápidas.

Como programador de Qt, com o KDE eu consigo contribuir, utilizar as múltiplas ferramentas oferecidas pela comunidade e possui um design mais parecido com o do Windows. Tudo isso, consumindo menos recursos. A distribuição mais conhecida é o KUbuntu.

KDE e GNOME são dois ambientes de desktop populares para sistemas operacionais Linux. Ambos têm seus próprios pontos fortes e fracos, e a escolha entre eles depende de suas preferências e necessidades pessoais.

O KDE é conhecido por seu rico conjunto de recursos e capacidade de personalização. Ele oferece um layout de área de trabalho tradicional confortável para a maioria dos usuários do Windows. A aparência consistente do KDE, mesmo com inúmeras melhorias ao longo dos anos, é um dos seus pontos fortes. O KDE também é conhecido pela sua liberdade na configuração e design de aplicações.

O GNOME, por outro lado, oferece um design de interface de usuário exclusivo e moderno. É uma boa escolha se você deseja uma experiência de desktop diferente. Os ícones, temas e papéis de parede do GNOME podem parecer melhores em relação aos padrões modernos. No entanto, ajustar o fluxo de trabalho pode demorar um pouco se você já estiver confortável com o layout tradicional do Windows. O GNOME é conhecido por sua base de fãs e suporte da comunidade.

Em resumo, o KDE é uma boa escolha se você prioriza a personalização e um layout de desktop tradicional. O GNOME é uma boa escolha se você deseja um design de interface de usuário exclusivo e moderno.