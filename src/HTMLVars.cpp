#include "htmlVars.h"

String messaggio = "pita";
int tempo_ms = 500; // 10 ms nel video
int decor = 0;
bool webFlag = true;
bool InterruptEn = true;
byte griglia1[8];
byte griglia2[8];
byte griglia3[8];
byte griglia4[8];

String StyleHtml = R"rawliteral(<!DOCTYPE html>
<html>
  <head>
    <title>Water Mike</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body {
        font-family: 'Segoe UI', sans-serif;
        margin: 0;
        padding: 0;
        background-color: #fff8f0;
      }
        header {
        background-color: #ff8000;
        color: white;
        padding: 10px 20px;
        display: flex;
        justify-content: space-between;
        align-items: center;
      }
      header h1 {
        margin: 0;
        font-size: 1.5em;
      }
      .logo {
        height: 80px;
      }
        .back-button {
        background: white;
        color: orange;
        border: none;
        padding: 5px 10px;
        font-size: 1em;
        cursor: pointer;
        border-radius: 5px;
      }
      main {
            margin: 30px auto;
            padding: 20px;
            background: white;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            text-align: center;
        }

        .mainIndex {
            max-width: 600px;
        }

      label {
        display: block;
        margin-top: 15px;
        font-weight: bold;
        color: #333;
      }
      input[type="text"],
      input[type="number"] {
        width: 100%;
        padding: 8px;
        margin-top: 5px;
        border: 1px solid #ccc;
        border-radius: 5px;
      }
      .checkbox-row {
        display: flex;
        align-items: center;
        margin-top: 15px;
      }
      .checkbox-row label {
        margin: 0 10px 0 0;
        font-weight: bold;
      }
      .form-actions {
        text-align: right;
        margin-top: 20px;
      }
      input[type="submit"] {
        padding: 10px 20px;
        background-color: #ff8000;
        color: white;
        border: none;
        border-radius: 5px;
        cursor: pointer;
      }
      input[type="submit"]:hover {
        background-color: #e67300;
      }
 #griglie {
      display: flex;
      flex-wrap: wrap;
      justify-content: center;
      padding: 20px;
    }
    .griglia {
        display: grid;
        grid-template-columns: repeat(8, 30px);
        grid-template-rows: repeat(8, 30px);
        gap: 4px;
        justify-content: center;
        margin: 0 auto;
      }
      .cell {
        width: 30px;
        height: 30px;
        background-color: #ddd;
        border-radius: 4px;
        cursor: pointer;
        transition: background-color 0.2s;
      }
      .cell.active {
        background-color: orange;
      }
      .button-bar {
        margin-top: 20px;
        display: flex;
        justify-content: center;
        gap: 20px;
      }
      .button-bar button {
        padding: 10px 20px;
        font-size: 1em;
        background-color: orange;
        color: white;
        border: none;
        border-radius: 6px;
        cursor: pointer;
      }
        @media (max-width: 768px) {
    .griglia {
        transform: scale(0.8); /* oppure cambia le dimensioni delle celle */
    }
}

@media (max-width: 480px) {
    .griglia {
        transform: scale(0.65); /* più compatto su telefoni piccoli */
    }
}
    .missile-panel {
  display: flex;
  flex-direction: column;
  gap: 20px;
  align-items: center;
  margin: 40px auto;
}

.arm-button {
  padding: 15px 30px;
  font-size: 16px;
  font-weight: bold;
  color: white;
  background-color: #444;
  border: 2px solid #ffc107;
  border-radius: 8px;
  box-shadow: 0 0 8px #ffc107;
  cursor: pointer;
  transition: 0.3s;
}

.arm-button.active {
  background-color: #0f0;
  box-shadow: 0 0 12px #0f0;
  border-color: #0f0;
}

    </style>
      </head>
  <body>)rawliteral";
String saveGrid;
String Logo64 = R"rawliteral(data:image/jpeg;base64,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")rawliteral";

String indexHtml;
void createIndexHtml()
{
  indexHtml = StyleHtml +
              R"rawliteral(
    <header>
      <h1>Water Mike</h1>
      <img class="logo" src=")rawliteral" +
              Logo64 +
              R"rawliteral(" alt="Logo">
    </header>
    <main class="mainIndex">
      <h2>Configurazione</h2>
      <form action="/" method="get">
        <label>Messaggio:</label>
        <input type="text" name="text" value=")rawliteral" +
              messaggio + R"rawliteral(">

        <div class="checkbox-row">
          <label for="flag">interrupt abilitati:</label>
          <input type="checkbox" id="flag" name="flag" )rawliteral" +
              (InterruptEn ? "checked" : "") + R"rawliteral(>
         <label>Tempo (ms):</label>
        <input type="number" name="time" value=")rawliteral" +
              String(tempo_ms) + R"rawliteral(">
              </div>

        <select name="decor">
        <option value="0" )rawliteral" +
              (decor == 0 ? "selected" : "") +
              R"rawliteral(>no decori</option>
        <option value="1" )rawliteral" +
              (decor == 1 ? "selected" : "") +
              R"rawliteral(>decori</option>
        <option value="-1" )rawliteral" +
              (decor == -1 ? "selected" : "") +
              R"rawliteral(>solo decori</option>
      </select>

      <div class="form-actions">
        <input type="submit" value="Invia">
      </div>
    </form>
    <form action="/griglia" method="get" style="margin-top: 20px;">
      <button type="submit">
        Vai alla griglia</button>
    </form>
    <div class="missile-panel">
      <button id="armButton" class="arm-button" onclick="ARM()">
        ARMAMENTO</button>
    </div>
    <script>
      function ARM() {
        fetch("/ARM?ARM=TRUE")
          .catch(err => console.error(err)); // todo pagina
      }
              window.onload = function() {
  const params = new URLSearchParams(window.location.search);

  if (params.has("text") || params.has("flag") || params.has("decor") || params.has("time")) {
      alert("Dati salvati!");
   }
};
    </script>
  </main>
  </body>
</html>
)rawliteral";
}

String gridHtml;
void creategridHtml()
{
  gridHtml = StyleHtml + R"rawliteral(
  </head>
  <body>
    <header>
      <button class="back-button" onclick="window.location.href='/'">Indietro</button>
      <img class="logo" src=")rawliteral" +
             Logo64 + R"rawliteral(" alt="Logo">
    </header>
  <main>
    <h2>Editor Griglia 8x8</h2>
    <div id="griglie">
      <div class="griglia" id="griglia1"></div>
      <div class="griglia" id="griglia2"></div>
      <div class="griglia" id="griglia3"></div>
      <div class="griglia" id="griglia4"></div>
    </div>
    <div class="button-bar">
      <button onclick="clearGrid()">Cancella</button>
      <button onclick="saveGrid()">Salva</button>
    </div>
  </main>
    <script>
      const grids = document.getElementsByClassName("griglia");

  // Crea le griglia 8x8  
      for (let g = 0; g < 8; g++){
        for (let y = 0; y < 8; y++) {
            for (let x = 0; x < 8; x++) {
                const cell = document.createElement("div");
               cell.classList.add("cell");
                cell.dataset.x = x;
               cell.dataset.y = y;
                cell.onclick = () => cell.classList.toggle("active");
                 grids[g].appendChild(cell);
             }
          }
      }

      function clearGrid() {
        document.querySelectorAll(".cell").forEach(cell => cell.classList.remove("active"));
      }

      function saveGrid() {
    const columns = Array(32).fill(0);  // 4 griglie da 8 colonne = 32

    const allCells = document.querySelectorAll(".cell");
    allCells.forEach((cell, idx) => {
        const x = parseInt(cell.dataset.x);
        const y = parseInt(cell.dataset.y);
        const gridIndex = Math.floor(idx / 64); // ogni griglia ha 64 celle
        const colIndex = gridIndex * 8 + x;

        if (cell.classList.contains("active")) {
            columns[colIndex] |= (1 << (7 - y));
        }
    });

    const hexString = columns.map(b => b.toString(16).padStart(2, "0")).join("");

        fetch("/saveGrid?data=" + hexString)
        .then(res => res.text())
        .then(msg => alert("griglia salvata"))
         .then(msg => window.location.href = '/')
          .catch(err => console.error(err));
      }
    </script>
  </body>
</html>
)rawliteral";
}
