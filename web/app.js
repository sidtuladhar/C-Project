// Connect to the WebSocket server
const socket = new WebSocket('ws://' + window.location.host + '/websocket');

const chat = document.getElementById('chat');
const messageInput = document.getElementById('message');
const sendButton = document.getElementById('send');

socket.onopen = () => {
    console.log('Connected to the WebSocket server');
};

socket.onmessage = (event) => {
    // Display the received message in the chat
    const msg = document.createElement('div');
    msg.textContent = event.data;
    chat.appendChild(msg);
    chat.scrollTop = chat.scrollHeight;
};

sendButton.onclick = () => {
    const message = messageInput.value;
    if (message) {
        // Send the message to the server
        socket.send(message);
        messageInput.value = '';
    }
};

// Allow sending the message with the Enter key
messageInput.addEventListener('keyup', (event) => {
    if (event.key === 'Enter') {
        sendButton.click();
    }
});
