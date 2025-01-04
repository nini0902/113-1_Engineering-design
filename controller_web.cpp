<!DOCTYPE html>
<html>
<head>
  <title>Car Control</title>
  <style>
    body {
      font-family: 'Courier New', Courier, monospace;
      background-color: #1a1a2e;
      color: #eaeaea;
      margin: 0;
      padding: 0;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      height: 100vh;
    }
    h1 {
      color: #00d4ff;
      font-size: 2.5rem;
      margin-bottom: 20px;
    }
    .button-container {
      display: flex;
      flex-direction: row;
      justify-content: center;
      align-items: center;
      margin: 10px 0;
    }
    button {
      width: 120px;
      height: 60px;
      margin: 10px;
      font-size: 18px;
      font-weight: bold;
      color: #fff;
      background-color: #27293d;
      border: 2px solid #00d4ff;
      border-radius: 8px;
      cursor: pointer;
      transition: all 0.3s ease;
    }
    button:hover {
      background-color: #00d4ff;
      color: #27293d;
    }
    button:active {
      transform: scale(0.95);
    }
    .grid-container {
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 10px;
    }
    .grid-item {
      display: flex;
      justify-content: center;
      align-items: center;
    }
    footer {
      margin-top: 20px;
      font-size: 0.9rem;
      color: #777;
    }
  </style>
</head>
<body>
  <h1>NodeMCU Car Control</h1>
  <div class="grid-container">
    <div class="grid-item"></div>
    <div class="grid-item">
      <button onclick="sendCommand('forward')">▲ Forward</button>
    </div>
    <div class="grid-item"></div>
    <div class="grid-item">
      <button onclick="sendCommand('left')">◀ Left</button>
    </div>
    <div class="grid-item">
      <button onclick="sendCommand('stop')">■ Stop</button>
    </div>
    <div class="grid-item">
      <button onclick="sendCommand('right')">▶ Right</button>
    </div>
    <div class="grid-item"></div>
    <div class="grid-item">
      <button onclick="sendCommand('backward')">▼ Backward</button>
    </div>
    <div class="grid-item"></div>
  </div>
  <footer>
    Control your car like a pro! Powered by NodeMCU and Web Interface.
  </footer>
  <script>
    function sendCommand(cmd) {
      fetch('/' + cmd) // 使用 Fetch 發送 AJAX 請求
        .then(response => {
          if (!response.ok) {
            throw new Error('Network response was not ok');
          }
          return response.text();
        })
        .then(data => console.log(data)) // 打印伺服器回應
        .catch(error => console.error('Error:', error));
    }
  </script>
</body>
</html>
