---
title: "Mushroom Map"
date: 2022-11-26T16:50:40Z
tags: []
draft: false
---
<link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.3/dist/leaflet.css"
     integrity="sha256-kLaT2GOSpHechhsozzB+flnD+zUyjE2LlfWPgU04xyI="
     crossorigin=""/>


<script src="https://unpkg.com/leaflet@1.9.3/dist/leaflet.js"
     integrity="sha256-WBkoXOwTeyKclOHuWtc+i2uENFpDZ9YPdf5Hf+D7ewM="
     crossorigin=""></script>

<div id="map"></div>
<style> #map { height: 800px; }</style>


<script>
    var map;

    function readFile(file) {
        var f = new XMLHttpRequest();
        f.open("GET", file, false);
        f.onreadystatechange = function() {
            if (f.readyState === 4 && f.status == 200) {
                var res = f.responseText;
                valueCallBack(res);
            }
        };
        f.send(null);
    }

    readFile('/docs/mushroom_data.txt');

    function valueCallBack(res){
        map = L.map('map').setView([51.71851, -1.25758], 15);

        L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
            maxZoom: 22,
            attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
        }).addTo(map);

        res = res.split("\n");

        for (let i = 1; i < res.length -1; i++) {
            let fungi = res[i].split(',');

            let marker = L.marker([fungi[3], fungi[4]])
                .addTo(map)
                .bindPopup("<h3>" + fungi[0] + "</h3>", {minWidth: 300 });

            let imageUrl = '/' + fungi[1];

            marker.on('mouseover', (function (marker, imageUrl, mushroomName) {
                return function (e) {
                    loadAndShowImage(marker, imageUrl, mushroomName);
                    this.openPopup();
                };
            })(marker, imageUrl, fungi[0])); // fungi[0] contains the name of the mushroom


            marker.on('mouseout', function (e) {
                this.closePopup();
            });

            marker.options.imageUrl = imageUrl; // Store image URL in marker options
        }
        L.control.scale().addTo(map);
    }

    function loadAndShowImage(marker, imageUrl, mushroomName) {
        var img = new Image();
        img.src = imageUrl;
        img.onload = function() {
            var popupContent = '<div style="pointer-events: auto;"><h4>' + mushroomName + '</h4><img src="' + imageUrl + '" /></div>';
            marker.getPopup().setContent(popupContent);
            marker.getPopup().update(); // Explicitly update popup content
        };
    }
</script>

<!-- remember to comment this out if other version is preferred. -->
<!-- This version of the script creates a panel below where the image of the mushroom is displayed. -->

<!-- <div id="image-panel"></div> 

<script>
    var map;
    var imagePanel = document.getElementById('image-panel');

    function readFile(file) {
        var f = new XMLHttpRequest();
        f.open("GET", file, false);
        f.onreadystatechange = function() {
            if (f.readyState === 4 && f.status == 200) {
                var res = f.responseText;
                valueCallBack(res);
            }
        };
        f.send(null);
    }

    readFile('/docs/mushroom_data.txt');

    function valueCallBack(res){
        map = L.map('map').setView([51.71851, -1.25758], 15);

        L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
            maxZoom: 22,
            attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
        }).addTo(map);

        res = res.split("\n");

        for (let i = 1; i < res.length -1; i++) {
            let fungi = res[i].split(',');

            let marker = L.marker([fungi[3], fungi[4]])
                .addTo(map)
                .bindPopup("<h3>" + fungi[0] + "</h3>", {minWidth: 300 });

            let imageUrl = '/' + fungi[1];

            marker.on('click', function (e) {
                showImageInPanel(fungi[0], imageUrl); // Display image in panel on marker click
            });

            marker.options.imageUrl = imageUrl; // Store image URL in marker options
        }
        L.control.scale().addTo(map);
    }

    function showImageInPanel(mushroomName, imageUrl) {
        var img = new Image();
        img.src = imageUrl;
        img.onload = function() {
            var imageElement = document.createElement('img');
            imageElement.src = imageUrl;
            imageElement.style.width = '30%';
            imagePanel.innerHTML = ''; // Clear previous content
            imagePanel.appendChild(imageElement); // Add image to panel
            var heading = document.createElement('h3');
            heading.textContent = mushroomName;
            imagePanel.insertBefore(heading, imagePanel.firstChild); // Add mushroom name above the image
        };
    }
</script> -->