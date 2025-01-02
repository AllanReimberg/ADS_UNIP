from __future__ import print_function

from datetime import datetime
import os
import shutil

from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError

import mysql.connector
from datetime import datetime
import time
import json

#----------------------------------------------------DEFINIÇÃO DE FUNÇÕES------------------------------------------------------------------------
def conectarBanco():
    global cursor
    global conexao
    #Conecta no Banco de Dados
    hospedeiro = "localhost"  
    usuario = "root"
    senha = "bmt@l0cadm1N"
    bd = "db_ticket" #Banco de Dados

    try:    
        conexao = mysql.connector.connect(
        host=hospedeiro,
        user=usuario,
        password=senha,
        database=bd,
        ) #Se conecta com o seu banco de dados

        cursor = conexao.cursor() #O cursor é o objeto que te possibilita mexer com o servidor do MySQL
            
    except: 
        print('Não foi possivel conectar') #Da um feedback ao usuario de que não houve uma falha

#Laço de repetição para que o algoritmo se repita enquanto estiver ligado

def descobrirArquivos():
        global caminho #Define a variavel 'caminho' como global, ou seja, todas as outras funções podem usar essa variavel
        arqsJson = []
        caminho = "C:/Users/Administrador/Meu Drive (nathan.oliveira@bmtech.com.br)/ORGANIC INTELLIGENCE" #Caminho completo da pasta de tickets novos
        listaArquivos = os.listdir(caminho + "/TICKETS NOVOS") #Lista todos os arquivos dentro da pasta especificada
        
        if len(listaArquivos) > 0: #Se a quantidade de arquivos na pasta for diferente de nenhum
            for arquivo in listaArquivos: #Para cada arquivo na lista de arquivos
                tamNome = len(arquivo) #Guarda a quantidade de caracteres que o nome do arquivo possuí
                if arquivo[-5: tamNome] == ".json": #Se as ultimas 5 letras forem igual a ".json"
                    arqsJson.append((arquivo)) #Adiciona na lista de arquivos json
            return arqsJson
        

#Descobrir qual foi o ultimo arquivo criado na pasta
def descobrirPrimeiro(listaArquivos):
        listaDatas = [] #Essa lista futuramente irá armazenar todas as datas de modificação e nome dos arquivos
        for arquivo in listaArquivos: #Para cada arquivo nas lista de arquivos
            dataMod = os.path.getmtime(f"{caminho}/TICKETS NOVOS/{arquivo}") #Pega a data de modificação de cada arquivo
            listaDatas.append((dataMod, arquivo)) #Adiciona a data de modificação seguido do nome do arquivo na lista
            
        listaDatas.sort(reverse=False) #Organiza na ordem crescente
        maisAntigo = listaDatas[0] #Pega o primeiro item da lista, ou seja, o arquivo mais antigo
        nomeArquivo = maisAntigo[1] #Separa apenas o nome do arquivo
        
        return nomeArquivo

#Ler o arquivo
def lerJSON(nomePrimeiro):
    global status
    global id
    global nomeS
    global nomeA
    global assunto
    try:
        with open(f'{caminho}/TICKETS NOVOS/{nomePrimeiro}', 'r') as arquivo_json: #Abre o arquivo JSON

            ticket = json.load(arquivo_json) #Aqui é onde fica armazenado todas as variaveis do JSON

        #Separar cada dado coletado no JSON
        status = ticket["status_ticket"] 
        id = ticket["id_ticket"]
        nomeS = ticket["nome_solicitante"]
        #nomeA = ticket["nome_agente"]
        nomeA = 'Estagiarios'
        assunto = ticket["assunto_ticket"]

        print(f"\nTicket:\nStatus:{status}\nId:{id}\nSolicitante:{nomeS}\nAgente:{nomeA}\nAssunto:{assunto}")

        #Chamar as funções e passar os parametros necessarios
        insertDataBase(status, id, nomeS, nomeA, assunto) #Chama a função para inserir os dados no banco de dados
        insertGoogleCalendar(id, nomeS, nomeA, assunto) #Chama a função de criar eventos no google calendario
                
        #Após fazer todo o processo
        moverLidos(nomePrimeiro) #Irá mover o arquivo lido para a pasta Tickets Lidos
    except:
        lixo(nomePrimeiro)
        
def prazoTermino():
    global previsaoHora
    global previsaoMinuto
    global previsaoSegundo

    prazoHora = 1
    prazoMinuto = 0
    prazoSegundo = 0

    previsaoHora = horaAtual + prazoHora
    previsaoMinuto = minutoAtual + prazoMinuto
    previsaoSegundo = segundoAtual + prazoSegundo

#Inserir dados no Banco de Dados
def insertDataBase(status, id, nomeS, nomeA, assunto):
    #Inserir dados na tabela 
    comando = f'INSERT INTO ticket(status_ticket, id_ticket, nome_solicitante, nome_agente, assunto_ticket, hora_alteração) VALUES ("{status}", {id}, "{nomeS}", "{nomeA}", "{assunto}", NOW());'
    reset = 'DELETE FROM ticket WHERE 1;ALTER TABLE ticket AUTO_INCREMENT = 1;'

    try:
        print('Cursor executando...')
        cursor.execute(comando) #Executa o comando
        conexao.commit() #Salva as alterações feitas no banco de dados
        print('Cursor executado e alterações salvas')
    except:
        print('Não foi possivel salvar as alterações feitas :(')

    cursor.close()
    conexao.close() #Fecha a conexão
    print("Conexão fechada.")      

#Inserir dados no Google Calendario
def insertGoogleCalendar(id, nomeS, nomeA, assunto):
        prazoTermino()

        creds = None  
        #O arquivo token.json armazena os tokens de acesso e atualização do usuário e é criado automaticamente quando o fluxo de autorização é concluído pela primeira vez

        if os.path.exists('token.json'):
            creds = Credentials.from_authorized_user_file('token.json', SCOPES)

        if not creds or not creds.valid:
            if creds and creds.expired and creds.refresh_token:
                creds.refresh(Request())
            else:
                flow = InstalledAppFlow.from_client_secrets_file(
                    'credentials.json', SCOPES)
                creds = flow.run_local_server(port=0)

            #Salva as credenciais para a próxima execução
            with open('token.json', 'w') as token:
                token.write(creds.to_json())


        try:
            service = build('calendar', 'v3', credentials=creds)

            event = { #Cria o corpo do evento
            'summary': f'{id} - {assunto}({nomeA})',
            'description': f'{assunto} - {nomeS}',
            'start': {
                'dateTime': f'{data_formatada}',
                'timeZone': 'UTC-3',
            },
            'end': {
                'dateTime': f'{dia_atual}T{previsaoHora}:{previsaoMinuto}:{previsaoSegundo}',
                'timeZone': 'UTC-3',
            },
            }

            event = service.events().insert (calendarId='2d42e09053f016214207d53150677071b9a23eaf330f3f4ae10c8685d402a398@group.calendar.google.com',    body=event).execute() #Insere o evento no Google Calendario
            print ('Evento criado com sucesso!: %s' % (event.get('htmlLink'))) #Retorna o link do evento que foi criado
        except HttpError as error:
            print('Ocorreu um erro: %s' % error)

def moverLidos(arquivo):
        os.rename(f"{caminho}/TICKETS NOVOS/{arquivo}", f"{caminho}/TICKETS LIDOS/{id}.json")

def lixo(arquivo):
    os.rename(f"{caminho}/TICKETS NOVOS/{arquivo}", f"{caminho}/LIXO/{arquivo}")
    print(f"Arquivo '{arquivo}' movido para o lixo.")

try: #Tenta conectar no banco
    conectarBanco()
except:
    print("Não conectado")
#---------------------------------------------------------MAIN----------------------------------------------------------------------------------
while True:    
    agora = datetime.now()

    dia_atual = agora.strftime('%Y-%m-%d')

    data_formatada = agora.strftime('%Y-%m-%d' + 'T' + '%H:%M:%S')

    horaAtual = int(agora.strftime('%H'))
    minutoAtual = int(agora.strftime('%M'))
    segundoAtual = int(agora.strftime('%S'))

    #print(data_formatada)

    # Se o escopo for modificado, delete o arquivo token.json e faça a autenticação novamente.
    SCOPES = ['https://www.googleapis.com/auth/calendar']
    
    time.sleep(0.5)

    conectarBanco()
    arquivosJson = descobrirArquivos()
    if len(arquivosJson) > 0:
        maisAntigo = descobrirPrimeiro(arquivosJson)
        lerJSON(maisAntigo) #Chama a função para ler o JSON e da como parametro o nome do arquivo mais antigo
    else:
        print("Nenhum arquivo encontrado")
    
