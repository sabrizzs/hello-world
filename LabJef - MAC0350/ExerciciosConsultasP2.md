# Conceitos

# Exercícios

**Consulta 0: Recuperar a data de nascimento e o endereço do empregado cujo nome é 'John B. Smith'.**

Em SQL

	SELECT DATANASC, ENDEREÇO
		FROM EMPREGADO
		WHERE PNOME = 'John' AND MNOME = 'B' AND SNOME = 'Smith'

Em Álgebra Relacional

	π DATANASC, ENDEREÇO (σ PNOME = 'John' AND MNOME = 'B' AND SNOME='Smith' (EMPREGADO)) 

**Consulta 1: Encontrar o nome e o endereço de todos os empregados que trabalham para o departamento 'Pesquisa'.**

Em SQL

	SELECT PNOME, SNOME, ENDEREÇO
	FROM EMPREGADO, DEPARTAMENTO
	WHERE DNOME = 'Pesquisa' AND DNUMERO = NDEP 

**Consulta 2: Para todo projeto localizado em 'Stafford', listar o número do projeto, o número do departamento responsável, e o sobrenome, endereço e data de nascimento do gerente responsável pelo departamento.**

Em SQL

	SELECT PNUMERO, DNUM, SNOME, ENDEREÇO, DATANASC
	FROM PROJETO, DEPARTAMENTO, EMPREGADO
	WHERE DNUM = DNUMERO AND SSNGER = NSS AND
		PLOCALIZAÇÃO = 'Stafford'

**Consulta 3: Encontrar os nomes de empregados que trabalham em todos os projetos controlados pelo departamento 5.**

Em SQL

	SELECT PNOME, SNOME
	FROM EMPREGADO
	WHERE ((SELECT PNRO
		FROM TRABALHA_EM
		WHERE NSS = NSSEMP)
		CONTAINS
		(SELECT PNUMERO
		FROM PROJETO
		WHERE DNUM = 5))

**Consulta 4: Fazer uma lista de números de projetos no qual um empregado, cujo sobrenome é 'Smith' , trabalha no projeto ou é gerente do departamento que controla o projeto.**

Em SQL

	(SELECT PNUMERO
	FROM PROJETO, DEPARTAMENTO, EMPREGADO
	WHERE DNUM=DNUMERO AND NSSGER=NSS AND SNOME='Smith')
	UNION
 	(SELECT PNUMERO
	FROM PROJETO, TRABALHA_EM, EMPREGADO
	WHERE PNUMERO=PNRO AND NSSEMP=NSS AND SNOME='Smith') 

**Consulta 5: Listar os nomes de todos os empregados com dois ou mais dependentes.**

Em SQL

	SELECT SNOME, PNOME
	FROM EMPREGADO
	WHERE ( SELECT COUNT (*)
	FROM DEPENDENTE
	WHERE NSS=NSSEMP) >= 2

**Consulta 6: Listar os nomes dos empregados que não possuem dependentes.**

Em SQL

	SELECT PNOME, SNOME
	FROM EMPREGADO
	WHERE NOT EXISTS ( SELECT *
			FROM DEPENDENTE
			WHERE NSS=NSSEMP)

**Consulta 7: Listar os nomes dos gerentes que têm ao menos um dependente.** 

Em SQL

	SELECT PNOME, SNOME
	FROM EMPREGADO
	WHERE EXISTS ( SELECT *
			FROM DEPENDENTE
			WHERE NSS=NSSEMP)
		AND
		EXISTS ( SELECT *
			FROM DEPARTAMENTO
			WHERE NSS=NSSGER)

## Apostila, pág 62

**a) Recuperar os nomes de empregados do departamento 5 que trabalham mais que 10 horas no projeto 'ProdutoX'.**

**b) Listar os nomes dos empregados que tenham um dependente com o mesmo nome (PNOME).**

**c) Encontrar os nomes de empregados que são diretamente supervisionados por 'Franklin Wong'.**

**d) Para cada projeto, listar o nome do projeto e o total de horas (de todos os empregados) gastos em cada projeto.**

**e) Recuperar os nomes dos empregados que trabalham em todos os projetos.**

**f) Recuperar os nomes dos empregados que não trabalham em quaisquer projetos.**

**g) Para cada departamento, recuperar o nome do departamento e a média salarial dos empregados que trabalham no departamento.**

**h) Recuperar a média salarial de todos os empregados femininos.**

**i) Encontrar os nomes e endereços de empregados que trabalham em ao menos um projeto localizado em Houston mas cujo departamento não possua localização em Houston.**

**j) Listar os sobrenomes dos gerentes de departamentos que não tenham dependentes.**

**k) Generalize a consulta i) acima para listar os nomes e endereços de empregados que trabalham em um projeto em alguma cidade , mas que o departamento não tenha nenhuma localização nessa cidade.** 

## P2 - 2019

**1.1. Encontrar o nome e o endereço de todos os empregados que trabalham para oo departamento 'Pesquisa'.**

**1.2. Encontrar os nomes dos empregados que trabalham em todos os projetos controlados pelo departamento 5.**

**1.3. Listar os nomes dos empregados que não possuem dependentes.**











  
