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

function valueCallBack(res){


	var map = L.map('map').setView([51.71851, -1.25758], 15);

	L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
		maxZoom: 19,
		attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
	}).addTo(map);

	res = (res.split("\n"));

	for (let i = 1; i < res.length -1; i++) {
		var fungi = res[i].split(',');

		var markerB = L.marker([fungi[3], fungi[4]], {title: "This is a title"})
			.addTo(map)
			.bindPopup("<H3>" +fungi[0] + "</><img src=" + '/' + fungi[1] + "/>",{minWidth: 200})
			.on('mouseover', function (e) {this.openPopup()})
			.on('mouseout', function (e) {this.closePopup()});
	}

}





</script>