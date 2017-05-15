----------------------- SEMPRARROLAR -----------------------

Programação - MIEIC - T7G09

Bernardo Manuel Costa Barbosa - up201503477
João Pedro Teixeira Pereira de Sá - up201506252

------------- Estado de Desenvolvimento --------------------

- O Projeto cumpre todas as funcionalidades que foram pedidas;

- Criar e remover uma linha ou um condutor;

- Alterar QUALQUER parâmetro de um condutor ou de uma linha (desde o seu ID, paragens e aos tempos entre paragens);

- Visualização da lista de TODAS as paragens, com o respetivo ID, frequência e lista de paragens;

- Visualização da lista de TODOS os condutores, com o respetivo ID, nome, limitações, turnos atribuídos e tempo por atribuir;

- Gerar Turnos para QUALQUER linha com os condutores existentes e respeitando as suas limitações;

- Reiniciar Turnos para QUALQUER linha, reiniciando também os turnos dos condutores atribuídos a essa linha;

- Reiniciar Turnos para QUALQUER condutor, reiniciando também os turnos das linhas atribuídas a esse condutor;

- Visualização do Horário Formatado de QUALQUER linha, em ambos os sentidos, com os respetivos tempos em cada paragem;

- Visualização do Horário Formatado de QUALQUER paragem, em ambos os sentidos, com os respetivos tempos a partir dessa mesma paragem, em todas as linhas a que esta pertence;

- Visualização de um Percurso entre duas QUAISQUER paragens, apresentando os percursos, se possíveis, com as respetivas durações e trajetos, desde a linha às paragens de escala (se existirem);

- Visualização dos Turnos de QUALQUER linha, de Segunda-feira a Domingo, com os respetivos tempos, autocarros e condutores (se estiverem atribuídos);

- Visualização dos Turnos de QUALQUER condutor (se estiverem atribuídos), de Segunda-feira a Domingo, com os respetivos tempos, autocarros e linhas;

- Visualização dos Turnos de QUALQUER autocarro, de QUALQUER linha, de Segunda-feira a Domingo, com os respetivos tempos e condutores;

-------------------- Melhorias/Decisões --------------------

- Consideramos o início diário às 7h e o respetivo fim às 22h;

- Consideramos, como grupo, que um turno corresponde ao tempo de ida e volta de uma linha;

- Como no enunciado não nos são fornecidas distâncias entre paragens, na funcionalidade nº8 (Percurso entre duas quaisquer paragens) optamos por apresentar os resultados por ordem crecente de tempo de viagem;

- Na visualização de um Percurso entre duas QUAISQUER paragens, optamos por apenas apresentar uma simples descrição de cada trajeto, comentando o código que imprime formatadamente o Horário de cada viagem que seja encontrada;

- Cada vez que um condutor ou uma linha são alterados, os seus turnos são reiniciados;

------------------- Agradecimentos/Apoios ------------------

http://www.cplusplus.com;
http://stackoverflow.com;

Professor Rui Camacho;
Professor Jorge Silva;

------------------------------------------------------------
