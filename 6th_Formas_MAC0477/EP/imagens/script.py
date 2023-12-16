import os

def extrair_detalhes(nome_imagem):
    # Extrair apenas o nome do arquivo sem o caminho
    nome_arquivo = os.path.splitext(os.path.basename(nome_imagem))[0]
    
    partes = nome_arquivo.split('_')
    classe = partes[0]
    item = partes[1]
    numero_item = partes[2]
    cor_fundo = partes[3]
    
    return f"Classe: {classe}\nObjeto: {item}\nID do objeto: {numero_item}\nCor do fundo: {cor_fundo}"

def criar_arquivo_txt(nome_imagem):
    detalhes = extrair_detalhes(nome_imagem)
    nome_arquivo_txt = nome_imagem.replace('.jpg', '.txt')  # Substitua .jpg pela extensão real das suas imagens, se for diferente
    
    with open(nome_arquivo_txt, 'w') as arquivo:
        arquivo.write(detalhes)

def main():
    diretorio = r"C:\Users\Sabrina\Downloads\mac0447"  # Substitua pelo caminho correto do seu diretório

    for nome_imagem in os.listdir(diretorio):
        if nome_imagem.endswith(".jpg"):  # Substitua .jpg pela extensão real das suas imagens, se for diferente
            criar_arquivo_txt(os.path.join(diretorio, nome_imagem))

if __name__ == "__main__":
    main()
