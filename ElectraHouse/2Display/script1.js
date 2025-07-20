function changeVideo(segmentId, newVideoSrc) {
    const segment = document.getElementById(segmentId);
    const video = segment.querySelector("video");
    video.src = newVideoSrc;
    video.play();
}

const socket = new WebSocket("ws://localhost:80");

socket.addEventListener("open", function(event) {
    console.log("WebSocket connected");
});

// Each display can have its own local state, or share state if needed.
// Use a local state variable if you need sequential logic:
let state = 0;

socket.addEventListener("message", function(event) {
    const msg = event.data.replaceAll(/\s/g, "").toString().toLowerCase();
    if (msg === "start") {
        window.location.reload();
    }
    if (parseInt(msg) == 1 && state == 0) {
        changeVideo(`segment1`, `videos/video2.mp4`);
        state++;
    }
    if (parseInt(msg) == 2 && state == 1) {
        changeVideo(`segment3`, `videos/video6.mp4`);
        state++;
    }
});