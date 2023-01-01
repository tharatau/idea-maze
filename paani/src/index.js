var canvas = document.createElement("canvas");
var context = canvas.getContext("2d");
var animationFrameID;

var panditSprite = {
    name: "Chota Pandit",
    h: 100,
    w: 100,
    x: 10,
    y: 40,
    mx: 20,
    mx: 30,
    color: null,
    image: function() {
        var panditImage = document.createElement("img");
        panditImage.src = "./pandit.png";
        panditImage.style.transform = "scaleX(-1)";
        return panditImage;
    },
    audio: function(no) {
        var panditAudio = document.createElement("audio");
        panditAudio.src = `./paani${no}.mp3`;
        return panditAudio;
    },
    jumps: 0,
    isJumping: false,
    move: function(direction) {
        if (direction === "left") {
            this.x -= this.mx;
        }
        if (direction === "right") {
            this.x += this.mx;
        }
        if (direction === "jump") {
            this.y -= this.mx;
            this.isJumping = true;
            this.jumps += 1;
            if (this.jumps % 2 !== 0) {
                this.audio(1).play();
            } else {
                this.audio(2).play();
            }
            if (this.isJumping === true) {
                setTimeout(() => {
                    this.y += this.mx;
                    this.isJumping = false;
                }, 1000);
            }
        }
    },
    render: function() {
        context.drawImage(this.image(), this.x, this.y, this.w, this.h);
    }
};

var waterSprite = {
    name: "water",
    h: 5,
    w: 20,
    x: 100,
    y: 125,
    color: "blue",
    render: function() {
        context.fillStyle = this.color;
        context.fillRect(this.x, this.y, this.w, this.h);
    }
};

var groundSprite = {
    name: "ground",
    h: 25,
    w: 250,
    x: 0,
    y: 125,
    color: "brown",
    render: function() {
        context.fillStyle = this.color;
        context.fillRect(this.x, this.y, this.w, this.h);
    }
};

var worldScene = {
    name: "world",
    h: 500,
    w: 250,
    x: 0,
    y: 0,
    color: "lightblue",
    render: function() {
        context.fillStyle = this.color;
        context.fillRect(this.x, this.y, this.w, this.h);
    }
};

document.addEventListener("keypress", function(event) {
    if (event.key === "a") {
        panditSprite.move("left");
    }
    if (event.key === "d") {
        panditSprite.move("right");
    }

    if (event.key === " " && panditSprite.isJumping === false) {
        panditSprite.move("jump");
    }

    if (event.key === "Enter") {
        render();
    }
})

function animate() {
    context.clearRect(0, 0, canvas.width, canvas.height);
    worldScene.render();
    groundSprite.render();
    waterSprite.render();
    panditSprite.render();
    window.requestAnimationFrame(animate);
}

function main() {
    document.getElementById("root").append(canvas);
    animate();
}

main();