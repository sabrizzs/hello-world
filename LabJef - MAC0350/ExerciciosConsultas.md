# Conceitos

# Exercícios

**Consulta 0: Recuperar a data de nascimento e o endereço do empregado cujo nome é 'John B. Smith'.**

Em SQL

	SELECT DATANASC, ENDEREÇO
		FROM EMPREGADO
		WHERE PNOME = 'John' AND MNOME = 'B' AND SNOME = 'Smith'

Em 

	π DATANASC, ENDEREÇO (σ PNOME = 'John' AND MNOME = 'B' AND SNOME='Smith' (EMPREGADO)) 
