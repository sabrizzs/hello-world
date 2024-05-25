 /* ==================================================
        cronometro.js

        Nome: Sabrina Araujo da Silva
        NUSP: 12566182

        Ao preencher esse cabeçalho com o meu nome e o meu número USP,
        declaro que todas as partes originais desse exercício programa (EP)
        foram desenvolvidas e implementadas por mim e que portanto não 
        constituem desonestidade acadêmica ou plágio.
        Declaro também que sou responsável por todas as cópias desse
        programa e que não distribui ou facilitei a sua distribuição.
        Estou ciente que os casos de plágio e desonestidade acadêmica
        serão tratados segundo os critérios divulgados na página da 
        disciplina.
        Entendo que EPs sem assinatura devem receber nota zero e, ainda
        assim, poderão ser punidos por desonestidade acadêmica.

        Abaixo descreva qualquer ajuda que você recebeu para fazer este
        EP.  Inclua qualquer ajuda recebida por pessoas (inclusive
        monitores e colegas). Com exceção de material da disciplina, caso
        você tenha utilizado alguma informação, trecho de código,...
        indique esse fato abaixo para que o seu programa não seja
        considerado plágio ou irregular.

        Exemplo:

            A minha função quicksort() foi baseada na descrição encontrada na 
            página https://www.ime.usp.br/~pf/algoritmos/aulas/quick.html.

        Descrição de ajuda ou indicação de fonte:



    ================================================== */

window.onload = main;
 
var isRunning = false;
var isPaused = false;
var isTimerMode = true;
var isReseted = true;

var currentTime = 0;
var typedTime = 0;

function main(){
    document.addEventListener("DOMContentLoaded", main);

    const modeButton = document.getElementById('mode');
    const startButton = document.getElementById('start')
    const pauseButton = document.getElementById('pause');
    const displayTime = document.getElementById('display-time');
    const titleMode = document.getElementById('title-mode')
    
    modeButton.addEventListener('click', modeCallback(modeButton, titleMode));
    startButton.addEventListener('click', startCallback(startButton, pauseButton, displayTime))
    pauseButton.addEventListener('click', pauseCallback(pauseButton, startButton));

    for (let i = 1; i <= 9; i++) {
        document.getElementById(String(i)).addEventListener('click', addNumber(i, displayTime));
    }
    document.getElementById('zero').addEventListener('click', addNumber(0, displayTime));
    document.getElementById('clear').addEventListener('click', clearDisplay(displayTime));
}

function updateDisplay(){
    const minutes = Math.floor(currentTime / 60000);
    const seconds = Math.floor((currentTime % 60000) / 1000);
    const milliseconds = currentTime % 1000;
    const displayText = `${String(minutes).padStart(2, '0')}:${String(seconds).padStart(2, '0')}:${String(milliseconds).padStart(2, '0').slice(0, 2)}`;
    document.getElementById('display-main').textContent = displayText;
};

function timeUpdate(startTime, startButton){

    currentTime = Date.now() - startTime;
    if(isRunning){
        if(isTimerMode){
            if(currentTime <= typedTime){
                updateDisplay();
                requestAnimationFrame(() => timeUpdate(startTime, startButton));
            } else {
                resetTime(startButton)
            }       
        } else {
            if (currentTime <= typedTime) {
                currentTime = typedTime - currentTime;
                updateDisplay();
                requestAnimationFrame(() => timeUpdate(startTime, startButton));
            } else resetTime(startButton);
        }
    } 
}

function resetTime(startButton){
        isRunning = false;
        isPaused = false;
        isReseted = true;

        if(isTimerMode) currentTime = typedTime
        else currentTime = 0
        updateDisplay();
        startButton.textContent = 'Start'

        console.log(`Finalizado`);
}

function moreThan59(displayTime){
    let currentText = displayTime.textContent;
    currentText = currentText.split('');
    let minutes = parseInt(currentText[0] + currentText[1]);
    let seconds = parseInt(currentText[3] + currentText[4]);
    let isNormalized = false;

    if (minutes > 59){
        currentText[0] = 5;
        currentText[1] = 9;
        minutes = 59
        isNormalized = true;
    }

    if (seconds > 59){
        currentText[3] = 5;
        currentText[4] = 9;
        seconds = 59
        isNormalized = true;
    }

    currentText = currentText.join('');
    displayTime.textContent = currentText[0] + currentText[1] + ':' + currentText[3] + currentText[4];
    typedTime = (minutes * 60000) + (seconds * 1000);

    if(isNormalized) console.log(`Tempo normalizado: ${displayTime.textContent}`)
}

function startCallback(startButton, pauseButton, displayTime){
    return function(){
        moreThan59(displayTime);

        if(!isRunning && !isPaused){
            if(isTimerMode) console.log(`Timer iniciado`);
            else console.log(`Cronômetro iniciado`);

            startButton.textContent = 'Stop'
            isRunning = true;
            isReseted = false;
            const startTime = Date.now();
            timeUpdate(startTime, startButton);

        } else {
            if(isTimerMode) console.log(`Timer resetado`);
            else console.log(`Cronômetro resetado`);

            startButton.textContent = 'Start'
            pauseButton.textContent = 'Pause';
            isRunning = false;
            isPaused = false;
            isReseted = true;
            currentTime = 0
            updateDisplay();
        }
    };
}

function pauseCallback(pauseButton, startButton){
    return function(){

        if(isRunning){
            if(isTimerMode) console.log(`Timer pausado`);
            else console.log(`Cronômetro pausado`);
    
            isRunning = false;
            isPaused = true;
            pauseButton.textContent = 'Run';

        } else if(!isReseted) {
            if(isTimerMode) console.log(`Timer despausado`);
            else console.log(`Cronômetro despausado`);
    
            isRunning = true;
            isPaused = false;
            pauseButton.textContent = 'Pause';

            const startTime = Date.now() - currentTime;
            timeUpdate(startTime, startButton);
        } else {
            console.log(`Botão desativado`);
        }
    };
}

function addNumber(number, displayTime){
    return function(){
        if(!isRunning && !isPaused) {
            const currentText = displayTime.textContent;
            displayTime.textContent = currentText[1] + currentText[3] + ':' + currentText[4] + number;
            typedTime = parseInt(parseInt(currentText[1] + currentText[3]) * 60000 + parseInt(currentText[4] + number) * 1000)

            console.log(`Número ${number} pressionado. Tempo: ${displayTime.textContent}`);
        } else {
            console.log(`Botão desativado`);
        }
    };
}

function clearDisplay(displayTime){
    return function(){
        if(!isRunning && !isPaused) {
            displayTime.textContent = '00:00'
            typedTime = parseInt('0')

            console.log(`Display limpo. Tempo: ${displayTime.textContent}`);
        } else {
            console.log(`Botão desativado`);
        }
    };
}

function modeCallback(modeButton, titleMode){
    return function(){
        if(!isRunning && !isPaused){
            if(isTimerMode){
                console.log(`Modo alterado para Cronômetro`);
    
                modeButton.textContent = 'Timer';
                titleMode.textContent = 'Crono';
                isTimerMode = false;
            } else if(!isTimerMode){
                console.log(`Modo alterado para Timer`);
    
                modeButton.textContent = 'Crono';
                titleMode.textContent = 'Timer';
                isTimerMode = true;
            }
        } else {
            console.log(`Botão desativado`);
        }
    };
}
    