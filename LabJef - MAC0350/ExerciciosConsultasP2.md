# Conceitos

## SQL

- SELECT

Forma geral:

	SELECT [ DISTINCT | ALL ] <lista de atributos>
	FROM <lista de tabelas>
	[ WHERE<condições> ]
	[ GROUP BY atributo ]
	[ HAVING <condições> ]
	[ ORDER BY atributo [ ASC | DESC ] ];

Seleciona O QUE se deseja na tabela resultado:

- ou * (para todos os atributos)
- ALL – inclui tuplas duplicadas (é o default)
- DISTINCT – elimina tuplas duplicadas
- FROM – DE ONDE retirar os dados necessários
- WHERE – CONDIÇÕES de seleção dos resultados.

Exemplo: Recuperar a data de aniversário e o endereço do empregado chamado 'John B. Smith'

	SELECT DATANASC, ENDERECO
	FROM EMPREGADO
	WHERE PNOME='John' AND MNOME='B’ AND SNOME='Smith’;

- PROJECT 

Exemplos: Recuperar a data de aniversário e o endereço dos empregados

	SELECT DATANASC, ENDERECO
	FROM EMPREGADO

- JOIN

Exemplo: Obter o nome e o endereço dos empregados que trabalham para o departamento de ‘Pesquisa’.

	SELECT PNOME, ENDERECO
	FROM EMPREGADO, DEPARTAMENTO
	WHERE DNOME = ‘Pesquisa' AND DNUMERO=DNUM;

- DIVISION

Exemplo: Encontrar os nomes de empregados que trabalham em todos os projetos controlados pelo departamento 5.

	SELECT PNOME, SNOME
	FROM EMPREGADO
	WHERE ( ( SELECT PNO
		FROM TRABALHA-EM
		WHERE NSS=ENSS )
		CONTAINS
			( SELECT PNUMERO
			FROM PROJETO
			WHERE DNUM=5 ) );

## Álgebra Relacional

σ π ⌧ ÷

Operações da teoria de conjunto
- Union
- Intersection
- Difference
- Cartesian Product

Operações para banco de dados relacionais
- Select
	- σ <condição de seleção> (<nome da relação>)
  	- exemplo: σ salário > 3000 (EMPREGADO)
	- seleciona subconjunto de tuplas

- Project
	- π <lista de atributos> (<nome da relação>)
	- exemplo: π sexo, salário (EMPREGADOS)
	- seleciona colunas da tabela

- Join
	- R ⌧ <condição join> S
	- exemplo: DEPARTAMENTO ⌧ gernss = nss EMPREGADO
	- combina duas relações com base em atributos

- Division
	- considere as relações:
 		- R(A, B), onde A e B são atributos de R
   		- S(B)
       	- R ÷ S retorna todos os valores de A que estão relacionados com os valores de B em S

## Cálculo Relacional

∃ ∀

Exemplo de SELECT

Recupere todos os empregados do sexo feminino

	{t | EMPREGADO(t) AND t.sexo = 'F'}

Exemplo de PROJECT

Recupere o nome e o endereço de todos os empregados

	{t.pnome, t.snome, t.endereço | EMPREGADO(t)}

Exemplo de JOIN

Recupere o nome e o endereço de todos os empregados que trabalham para o departamento 'Pesquisa'

	{t.pnome, t.snome, t.endereço | EMPREGADO(t) AND
					(∃d) (DEPARTAMENTO(d) AND
  						d.dnumero = p.dnum AND
    						d.gernss = m.nss)}

Exemplo de DIVISION

Liste o nome de todos os empregados que trabalham em todos os projetos

	{e.pnome | EMPREGADO(e) AND
		(∀p)(PROJETO(p) => (∃w)(TRABALHA_EM(w) AND
  					w.pno = p.numero AND
       					w.enss = e.nss}
  			

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

Em Álgebra Relacional

	PESQUISA_DEPTO←σ DNOME = 'Pesquisa' (DEPARTAMENTO)
	PESQUISA_DEPTO_EMPS←(PESQUISA_DEPTO ⌧ DNÚMERO = NDEP EMPREGADO)
	RESULT←π PNOME, SNOME, ENDEREÇO (PESQUISA_DEPTO_EMPS)

**Consulta 2: Para todo projeto localizado em 'Stafford', listar o número do projeto, o número do departamento responsável, e o sobrenome, endereço e data de nascimento do gerente responsável pelo departamento.**

Em SQL

	SELECT PNUMERO, DNUM, SNOME, ENDEREÇO, DATANASC
	FROM PROJETO, DEPARTAMENTO, EMPREGADO
	WHERE DNUM = DNUMERO AND SSNGER = NSS AND
		PLOCALIZAÇÃO = 'Stafford'

Em Álgebra Relacional

	STAFFORD_PROJS←σ PLOCALIZAÇÃO = 'Stafford' (PROJETO)
	CONTR_DEPT←(STAFFORD_PROJS ⌧ DNUM = DNÚMERO DEPARTAMENTO)
	PROJ_DEPT_MGR←(CONTR_DEPT ⌧ SSNGER = NSS EMPREGADO)
	RESULT←π PNÚMERO, DNUM, SNOME, ENDEREÇO, DATANASC (PROJ_DEPT_MGR)

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

Em Álgebra Relacional

	DEPT5_PROJS(PNO)←π PNÚMERO (σ DNUM=5 (PROJETO)))
	EMP_PROJ(NSS, PNO)←π NSSEMP, PNRO (TRABALHA_EM)
	RESULT_EMP_SSNS←EMP_PROJ ÷ DEPT5_PROJS
	RESULT←π SNOME, PNOME (RESULT_EMP_SSNS * EMPREGADO) 

**Consulta 4: Fazer uma lista de números de projetos no qual um empregado, cujo sobrenome é 'Smith' , trabalha no projeto ou é gerente do departamento que controla o projeto.**

Em SQL

	(SELECT PNUMERO
	FROM PROJETO, DEPARTAMENTO, EMPREGADO
	WHERE DNUM=DNUMERO AND NSSGER=NSS AND SNOME='Smith')
	UNION
 	(SELECT PNUMERO
	FROM PROJETO, TRABALHA_EM, EMPREGADO
	WHERE PNUMERO=PNRO AND NSSEMP=NSS AND SNOME='Smith') 

Em Álgebra Relacional

	SMITH(NSSEMP)← π NSS (σ SNOME='Smith' (EMPREGADO))
	SMITH_WORKER_PROJS← π PNRO (TRABALHA_EM * SMITH)
	MGRS←π SNOME, DNÚMERO (EMPREGADO ⌧ NSS = NSSGER DEPARTAMENTO)
	SMITH_MGS←σ SNOME = 'Smith' (MGRS)
	SMITH_MANAGED_DEPTS(DNUM)←π DNÚMERO (SMITH_MGRS)
	SMITH_MGR_PROJS(PNRO)←π PNÚMERO (SMITH_MANAGED_DEPTS * PROJETO)
	RESULT←(SMITH_WORKER_PROJS ∪ SMITH_MGR_PROJS) 

**Consulta 5: Listar os nomes de todos os empregados com dois ou mais dependentes.**

Em SQL

	SELECT SNOME, PNOME
	FROM EMPREGADO
	WHERE ( SELECT COUNT (*)
	FROM DEPENDENTE
	WHERE NSS=NSSEMP) >= 2

Em Álgebra Relacional

	T1(NSS, NO_DE_DEPS)←NSSEMP ℑ COUNT NOMEDEPENDENTE (DEPENDENTE)
	T2←σ NO_DE_DEPS >= 2 (T1)
	RESULT←π SNOME, PNOME (T2 * EMPREGADO) 

**Consulta 6: Listar os nomes dos empregados que não possuem dependentes.**

Em SQL

	SELECT PNOME, SNOME
	FROM EMPREGADO
	WHERE NOT EXISTS ( SELECT *
			FROM DEPENDENTE
			WHERE NSS=NSSEMP)

Em Álgebra Relacional

	TODOS_EMPS←π NSS (EMPREGADO)
	EMPS_COM_DEPS(NSS)←π NSSEMP (DEPENDENTE)
	EMPS_SEM_DEPS←(TODOS_EMPS - EMPS_COM_DEPS)
	RESULT←π SNOME, PNOME (EMPS_SEM_DEPS * EMPREGADO) 

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

Em Álgebra Relacional

	MGRS(NSS)←π NSSGER (DEPARTAMENTO)
	EMPS_COM_DEPS(NSS)←π NSSEMP (DEPENDENTE)
	MGRS_COM_DEPS←(MGRS ∩ EMPS_COM_DEPS)
	RESULT←π SNOME, PNOME (MGRS_COM_DEPS * EMPREGADO) 

**Consulta 8: Encontre todos os empregados cujos salários estejam acima de R$3.500,00.**

Em Cálculo Relacional

	{t | EMPREGADO(t) AND t.SALARIO > 3500} 

**Consulta 9: Dê apenas os nomes e sobrenomes dos empregados cujos salários estejam acima de R$3.500,00.**

Em Cálculo Relacional

	{t.NOME, t.SOBRENOME | EMPREGADO(t) AND t.SALARIO > 3500}

**Consulta 10: Selecione o nome e o endereço dos empregados que trabalham para o departamento de ‘Informática’.**

Em Cálculo Relacional

	{t.NOME, t.SOBRENOME, t.ENDERECO | EMPREGADO(t) AND (∃ d) (DEPARTAMENTO (d)
 	AND d.NOMED = ‘Informática’ AND d.NUMERODEP = t.NUD)} 

**Consulta 11: Para cada projeto localizado em ‘São Paulo’, liste o número do mesmo, o nome do departamento proponente, bem como sobrenome, data de nascimento e endereço do gerente responsável.**

Em Cálculo Relacional

	{p.NUMEROP, p.NUMD, m.SOBRENOME, m.DATANASCIMENTO, m.ENDERECO |
	PROJETO(p) AND EMPREGADO(m) AND p.LOCALIZACAO = ‘São Paulo’ AND ((∃ d)
	(DEPARTAMENTO(d) AND d.NUMD = d.NUMERODEP AND d.NSSGER = m.NSS) )}

**Consulta 12: Encontre os nomes dos empregados que trabalham em todos os projetos controlados pelo departamento de número 5.**

Em Cálculo Relacional

	{e.SOBRENOME, e.NOME | EMPREGADO(e) AND ((∀ x) (NOT(PROJETO(x)) OR
	NOT(x.NUMD = 5) OR ((∃ w) (TRABALHA_EM(w) AND w.NSSE = e.NUMEROP AND
	x.NUMEROP = w.NUMP))))} 

## Apostila, pág 62

**a) Recuperar os nomes de empregados do departamento 5 que trabalham mais que 10 horas no projeto 'ProdutoX'.**

Em Álgebra Relacional σ π ⌧ ÷

	DEP5 <- σ ndep = 5 (EMPREGADO)
	PRODX <- (σ pnome = 'ProdutoX' (PROJETO)) ⌧ pnumero = pnro TRABALHA_EM
	EMPDEP5 <- (PRODX σ horas > 10) ⌧ nssemp = nss DEP5
	NOMES <- π pnome, snome EMPDEP5

Em Cálculo Relacional ∃ ∀

	{e.pnome, e.snome | EMPREGADO(e) AND e.ndep = 5 AND
				(∃ p,t) (PPROJETO(p) AND TRABALHA_EM(t) AND
   				p.pnome = 'ProjetoX' AND p.pnumero = t.pnro AND
      				t.horas > 10 AND t.nssemp = e.nss)}

Em SQL

	SELECT DISTINCT PNOME, SNOME
 	FROM EMPREGADO, PROJETO, TRABALHA_EM
  	WHERE NDEP='5' AND 
   	      PNOME='ProjetoX' AND
	      PNUMERO=PNRO AND 
              HORAS > 10 AND
	      NSSEMP = NSS

**b) Listar os nomes dos empregados que tenham um dependente com o mesmo nome (PNOME).**

Em Álgebra Relacional σ π ⌧ ÷

	DEPEND <- EMPREGADO ⌧ nss = nssemp DEPENDENTE
	MSMNOME <- σ nomedependente = pnome (DEPEND)
	NOMES <- π pnome, snome (MSMNOME)

Em Cálculo Relacional ∃ ∀

	{e.pnome, e.snome | EMPREGADO(e) AND
				(∃d)(DEPENDENTE(d) AND
   					e.nss = d.nssemp AND d.nomedependente = e.pnome)}
   				

Em SQL

	SELECT DISTINCT PNOME, SNOME
	FROM EMPREGADO, DEPENDENTE
	WHERE NSS=NSSEMP AND 
 	      PNOME=NOMEDEPENDENTE

**c) Encontrar os nomes de empregados que são diretamente supervisionados por 'Franklin Wong'.**

Em Álgebra Relacional σ π ⌧ ÷

	FRANKW <- σ pnome = 'Franklin' AND snome = 'Wong' (EMPREGADO)
	SPVFRANK <- FRANKW ⌧ nss=nsssuper EMPREGADO
	NOMES <- π pnome, snome (SPVFRANK) 

Em Cálculo Relacional ∃ ∀

	{e.pnome, e.snome | EMPREGADO(e) AND
 				(∃f)(EMPREGADO(f) AND
     					f.pnome = 'Franklin' AND f.snome = 'Wong' AND
	  				e.nsssuper = f.nss)}

Em SQL

	SELECT DISTINCT emp.pnome, emp.mnome, emp.snome
 	FROM EMPREGADO emp, EMPREGADO sup
  	WHERE sup.pnome='Franklin' AND sup.snome='Wong' AND
   	      emp.nsssuper=sup.nss

**d) Para cada projeto, listar o nome do projeto e o total de horas (de todos os empregados) gastos em cada projeto.**

Em Álgebra Relacional σ π ⌧ ÷

	PROJETOS <- PROJETO ⌧ pnro=pnumero TRABALHA_EM
 	HORAS(pnome, totalhoras) <- pnome F sum horas (PROJETOS)

Em Cálculo Relacional ∃ ∀

	Não é possível representar utilizando cálculo de tuplas devido à presença de função de agregação.

Em SQL

	SELECT DISTINCT pnome, sum(horas)
 	FROM PROJETO, TRABALHA_EM
  	WHERE pnro=pnumero
   	GROUP BY pnome

**e) Recuperar os nomes dos empregados que trabalham em todos os projetos.**

Em Álgebra Relacional σ π ⌧ ÷

	PROJETOS <- π pnumero (PROJETO)
 	EMPREGADOS <- EMPREGADO ⌧ nss=nssemp TRABALHA_EM
  	EMPATRIBUTOS(pnome, mnome, snome, pnumero) <- π pnome, mnome, snome, pnumero (EMPREGADOS)
   	TODOS <- EMPATRIBUTOS ÷ PROJETOS
    	RESULT <- π pnome, mnome, snome (TODOS)

Em Cálculo Relacional ∃ ∀



Em SQL

	SELECT DISTINCT pnome, mnome, snome
 	FROM EMPREGADO
  	WHERE NOT EXISTS ( SELECT *
   				FROM projeto
       				WHERE pnumero NOT IN (SELECT pnro
	   						FROM TRABALHA_EM
	  						WHERE nssemp = nss

**f) Recuperar os nomes dos empregados que não trabalham em quaisquer projetos.**

**g) Para cada departamento, recuperar o nome do departamento e a média salarial dos empregados que trabalham no departamento.**

**h) Recuperar a média salarial de todos os empregados femininos.**

**i) Encontrar os nomes e endereços de empregados que trabalham em ao menos um projeto localizado em Houston mas cujo departamento não possua localização em Houston.**

**j) Listar os sobrenomes dos gerentes de departamentos que não tenham dependentes.**

**k) Generalize a consulta i) acima para listar os nomes e endereços de empregados que trabalham em um projeto em alguma cidade , mas que o departamento não tenha nenhuma localização nessa cidade.** 

## P2 - 2019

**1.1. Encontrar o nome e o endereço de todos os empregados que trabalham para o departamento 'Pesquisa'.**

**1.2. Encontrar os nomes dos empregados que trabalham' em todos os projetos controlados pelo departamento 5.**

**1.3. Listar os nomes dos empregados que não possuem dependentes.**











  
