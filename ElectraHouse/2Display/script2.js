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

let state = 0;

socket.addEventListener("message", function(event) {
    const msg = event.data.replaceAll(/\s/g, "").toString().toLowerCase();
    if (msg === "start") {
        window.location.reload();
    }
    if (parseInt(msg) == 3 && state == 0) {
        changeVideo(`segment4`, `videos/video8.mp4`);
        changeVideo(`segment2`, `videos/video4.mp4`);
        state++;
    }
});