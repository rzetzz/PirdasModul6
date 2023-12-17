function updateData(){
    $.ajax({
        url:'data.php',
        type: 'GET',
        dataType: 'json',
        success: function(data) {
            $('#kondisi').text(data.kondisi);
            $('#led').text(data.led);
            $('#buzzer').text(data.buzzer);
            updateVisualization(data);
            
        },
        error: function(jqXHR, textStatus, errorThrown) {
            console.error('Error:', textStatus, errorThrown);
            alert("test");
            
        },
        complete: function() {
            
            setTimeout(updateData, 100);
        }
    })
}

var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(75, 500 / 500, 0.1, 1000);
var renderer = new THREE.WebGLRenderer();
renderer.setSize(500, 500);
document.getElementById('visualization-container').appendChild(renderer.domElement);
renderer.setClearColor(0xffffff);

var geometry = new THREE.BoxGeometry(1,2,0.5);
var material = new THREE.MeshStandardMaterial({ color: 0x00ff00 });
var cube = new THREE.Mesh(geometry, material);
scene.add(cube);

var spotLight = new THREE.SpotLight(0xffffff);
spotLight.position.set(20, 20, 20);
spotLight.castShadow = true; // Mengaktifkan bayangan dari spotlight
scene.add(spotLight);

scene.receiveShadow = true;
camera.position.z =0;

camera.position.x =3;
camera.rotation.z =THREE.MathUtils.degToRad(90);
camera.rotation.y =THREE.MathUtils.degToRad(90);





function updateVisualization(data) {
    // Manipulasi objek 3D (misalnya, rotasi berdasarkan data MPU6050)
    cube.rotation.x = THREE.MathUtils.degToRad(data.x);
    cube.rotation.y = THREE.MathUtils.degToRad(data.y);
    cube.rotation.z = 0;   
    renderer.render( scene, camera );
}



updateData();