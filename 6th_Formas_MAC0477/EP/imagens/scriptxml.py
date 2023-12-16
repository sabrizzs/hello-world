import os
import xml.etree.ElementTree as ET
from datetime import datetime

def extrair_detalhes(nome_imagem):
    nome_arquivo = os.path.splitext(os.path.basename(nome_imagem))[0]
    partes = nome_arquivo.split('_')

    classe = partes[0]
    diretorio = f"{classe}/{nome_arquivo}"
    item = partes[1]
    numero_item = partes[2]
    cor_fundo = partes[3]
	
    
    return diretorio,classe, item, numero_item, cor_fundo

def criar_xml(diretorio, classe, item, numero_item, cor_fundo, root):
    obj = ET.SubElement(root, "object")

    ET.SubElement(obj, "DIR").text = diretorio
    ET.SubElement(obj, "CLASS_NAME").text = classe
    ET.SubElement(obj, "OBJ_ID").text = item
    ET.SubElement(obj, "OBJ_NUM").text = numero_item
    ET.SubElement(obj, "BACKGROUND").text = cor_fundo

def main():
    diretorio = r"C:\Users\Sabrina\Downloads\mac0447"

    root = ET.Element("annotations")

    for nome_imagem in os.listdir(diretorio):
        if nome_imagem.endswith(".jpg"):
            diretorio, classe, item, numero_item, cor_fundo = extrair_detalhes(nome_imagem)
            criar_xml(diretorio, classe, item, numero_item, cor_fundo, root)

    tree = ET.ElementTree(root)
    nome_arquivo_xml = "imagens_annotations.xml"
    tree.write(nome_arquivo_xml)

if __name__ == "__main__":
    main()
