# Projeto prático para temporização no Raspberry Pi Pico W
  - **Desenvolvedor:** <ins>Gabriel Cavalcanti Coelho</ins>;

###  Implementação das atividades propostas na aula síncrona do dia 29/01 do EmbarcaTech utilizando o simulador Wokwi e a placa BitDogLab. As atividades envolvem a utilização de temporizadores periódicos e temporizadores de disparo (one-shot) para controle de LEDs.

### Atividade 1: Temporizador Periódico:
#### Desenvolvimento de um semáforo com alteração automática de estado a cada 3 segundos.
Funcionamento:
  - O semáforo inicia com o LED vermelho aceso;
  - A cada 3 segundos, o estado muda na seguinte sequência:
      1. Vermelho → Amarelo;
      2. Amarelo → Verde;
      3. Verde → Vermelho.
  - O terminal exibe um contador de segundos e indica quando ocorre a troca de estado.


### Atividade 2: Temporizador de Disparo (One Shot):
#### Desenvolvimento de um sistema de temporização para acionamento de LEDs ao pressionar um botão.
Funcionamento:
  - No início, os LEDs estão apagados, e o botão é configurado como entrada com um pull-up interno ativado;
  - Quando o botão é pressionado:
      1. Todos os LEDs acendem simultaneamente.
      2. Um temporizador inicia um ciclo de desligamento progressivo dos LEDs, ocorrendo a cada 3 segundos;
      3. Após 3 segundos: O LED azul apaga;
      4. Após 6 segundos: O LED vermelho apaga;
      5. Após 9 segundos: O LED verde apaga e o sistema retorna ao estado inicial.
  - Durante o ciclo, novas pressões do botão são ignoradas até que todos os LEDs tenham sido apagados;
  - O terminal exibe mensagens com o tempo de acionamento do botão e de cada etapa do alarme.
