---
title: "NTC Calculator"
date: 2022-07-18T14:29:23+01:00
tags: []
draft: false
---

<!-- help from - https://jsfiddle.net/red_stapler/u5aanta8/1/ -->


<style>
label{
    display: inline-block;
    float: left;
    clear: left;
    width: 100px;
    text-align: right;
}
input {
  display: inline-block;
  float: left;
}
</style>


<div class="container">
  <div class="row">
    <div class="col">
  <div>
      <div class="row"><label>B:</label><input  type="text" id="B" value="3450" /></div>
      <div class="row"><label>R2:</label><input  type="text" id="R_div" value="12000" /></div>
      <div class="row"><label>R25:</label><input  type="text" id="R25" value="10000" /></div>
      <div class="row"><label>Vcc:</label><input  type="text" id="vcc" value="3.3" /></div>
      <div class="row"><label></label><input  type="submit" onclick="adddata()" /></div>
      
  </div>
    </div>
  <div class="col">
<p align="center"> 
<img src="/misc/images/NTC_circuit.png" alt="drawing" width="150"/>
</p>

  </div>
</div>
</div>


<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/3.8.0/chart.min.js"></script>
<canvas id="myChart"></canvas>

<script>

function makeArr(startValue, stopValue, cardinality)
{
  var arr = [];
  var step = (stopValue - startValue) / (cardinality - 1);
  for (var i = 0; i < cardinality; i++) {
    arr.push((startValue + (step * i)).toFixed(3) ) ;
  }
  return arr;
}


function calculate_T()
{
  // let R25 = 10000;
  let R25 = Number(document.getElementById("R25").value);
  let T25 = 25 + 273.15;
  let B = Number(document.getElementById("B").value);
  let R_div =  Number(document.getElementById("R_div").value);
  let vcc = Number(document.getElementById("vcc").value);
  let n = 100;

  let vo = makeArr(0.1 ,vcc,n);
  let calc_r = [];

  for (var i = 0; i < n-1;i++) {
    calc_r.push( (vo[i] * R_div) / (vcc - vo[i]) );
  }

  let r_inf = [];
  for (var i = 0; i < n-1;i++) {
    r_inf.push( R25 * Math.exp(-B/T25) );
  }

  let T = [];
  for (var i = 0; i < n-1;i++) {
    T.push( (B / Math.log(calc_r[i]/ r_inf[i])) - 273.15  );
  }

  return T;
}


	let n = 100;
  let vcc = Number(document.getElementById("vcc").value);
	let vo = makeArr(0.1 ,vcc,n);

  let y = calculate_T();

  var ctx = document.getElementById("myChart").getContext("2d");

  var myChart = new Chart(ctx, {
   	type: "line",
   	data: {
      	labels: vo,
      	datasets: [
        	{
          	label: "Temperature [C]",
          	data : y,
          	backgroundColor: "rgba(153,205,1,0.6)",
          	fill : true
        	},
      	],
    	},
      options: {
          responsive: true,
          legend: {
              display: true
          },
          scales: {
          	x:[{
          		title:{
          			display: true,
          			text: 'your title'
          		}
          	}]         
          }
      }
  });


function adddata(){
  myChart.data.datasets[0].data = calculate_T();
  let vcc = Number(document.getElementById("vcc").value);
  myChart.data.labels= makeArr(0.1,vcc,100);
  myChart.update();
}
  </script>


### Equations

<div>
Characterise the NTC thermistor using the Beta method.

$$r_{\infty} =  R25 * exp \left(\frac{-B}{T25}\right)$$

Calculate the thermistor resistance from voltage and then use this to calculate temperature

$$ R = \frac{V_{out} \cdot R_2}{V_{cc} - V_{out}} $$ 

$$ T = \frac{B}{\ln(R/r_{\infty})}$$


</div>

<!-- <p align="center"> 
<img src="/misc/images/NTC_circuit.png" alt="drawing" width="300"/>
</p>
<br>
 -->


