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
    var marker; // Declare marker globally
    var map;    // Declare map globally

    function readFile(file)
    {
        var f = new XMLHttpRequest();
        f.open("GET", file, false);
        f.onreadystatechange = function()
        {
            if(f.readyState === 4 && f.status == 200) // 4 == DONE
            {
                var res= f.responseText;
                valueCallBack(res)   
            }
        }
        f.send(null);
    }

    readFile('/docs/mushroom_data.txt');


    function updateMarker() {
        // Get current location
        if (navigator.geolocation) {
            navigator.geolocation.getCurrentPosition(function(position) {
                var pos = {
                    lat: position.coords.latitude,
                    lng: position.coords.longitude
                };

                // Update marker position
                marker.setLatLng(pos);
                // map.setView(pos);
            }, function() {
                // Handle errors, e.g., user denied location access
                console.error('Error: The Geolocation service failed.');
            });
        } else {
            // Browser doesn't support Geolocation
            console.error('Error: Your browser doesn\'t support geolocation.');
        }
    }


    function valueCallBack(res){


    	var map = L.map('map').setView([51.71851, -1.25758], 15);

    	L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    		maxZoom: 22, // was 19 
    		attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
    	}).addTo(map);

    	res = (res.split("\n"));

    	for (let i = 1; i < res.length -1; i++) {
    		var fungi = res[i].split(',');

    		// var markerB = L.marker([fungi[3], fungi[4]], {title: "This is a title"})
            var marker = L.marker([fungi[3], fungi[4]])
    			.addTo(map)
    			.bindPopup("<H3>" +fungi[0] + "</><img src=" + '/' + fungi[1] + "/>",{minWidth: 300})
    			.on('mouseover', function (e) {this.openPopup()})
    			.on('mouseout', function (e) {this.closePopup()});
    	}
        L.control.scale().addTo(map);

        // Get current location
        if (navigator.geolocation) {
            navigator.geolocation.getCurrentPosition(function(position) {
                var pos = {
                    lat: position.coords.latitude,
                    lng: position.coords.longitude
                };


                var redIcon = L.icon({
                    iconUrl: 'https://raw.githubusercontent.com/pointhi/leaflet-color-markers/master/img/marker-icon-2x-red.png',
                    iconSize: [25, 41],
                    iconAnchor: [12, 41],
                    popupAnchor: [1, -34],
                    shadowSize: [41, 41],
                    shadowUrl: 'https://cdnjs.cloudflare.com/ajax/libs/leaflet/1.7.1/images/marker-shadow.png'
                });

                // Add a marker for the user's current position
                var marker = L.marker(pos, { icon: redIcon })
                    .addTo(map)
                    .bindPopup("You are here");
                
                setInterval(updateMarker, 1000);

                // map.setView(pos);
            }, function() {
                // Handle errors, e.g., user denied location access
                alert('Error: The Geolocation service failed.');
            });
        } else {
            // Browser doesn't support Geolocation
            alert('Error: Your browser doesn\'t support geolocation.');
        }
    }
</script>