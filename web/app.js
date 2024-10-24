// WebSocket connection
const socket = new WebSocket('ws://' + window.location.host + '/websocket');

const chat = document.getElementById('chat');
const messageInput = document.getElementById('message');
const sendButton = document.getElementById('send');
const searchPeersButton = document.getElementById('search-peers');
const peersList = document.getElementById('peers-list');

socket.onopen = () => {
    console.log('Connected to the WebSocket server');
};

socket.onmessage = (event) => {
    const data = JSON.parse(event.data);

    if (data.type === 'peer_list') {
        // Clear the current peer list
        peersList.innerHTML = '';

        // Display each peer in the list
        data.peers.forEach(peer => {
            const peerItem = document.createElement('div');
            peerItem.textContent = `Found peer: ${peer}`;
            peersList.appendChild(peerItem);
        });
    } else {
        // Handle chat messages
        const msg = document.createElement('div');
        msg.textContent = event.data;
        chat.appendChild(msg);
        chat.scrollTop = chat.scrollHeight;
    }
};

sendButton.onclick = () => {
    const message = messageInput.value;
    if (message) {
        socket.send(message);
        messageInput.value = '';
    }
};

searchPeersButton.onclick = () => {
    socket.send(JSON.stringify({ type: 'search_peers' }));
};
