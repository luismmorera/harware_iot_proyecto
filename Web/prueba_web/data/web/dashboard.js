/* globals Chart:false, feather:false */

(() => {
  'use strict'

  feather.replace({ 'aria-hidden': 'true' })

  let xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200){
      const jsonObj = JSON.parse(this.responseText);
      
      document.getElementById("titulo_grafica").innerHTML += (" (en el mes de " + jsonObj.pasos.mes + ")");
      
      //Rellenar gráfica de los pasos
      let days=[];
      let values=[];
      
      for (const i in jsonObj.pasos.muestras) {
        days.push(jsonObj.pasos.muestras[i].dia);
        values.push(jsonObj.pasos.muestras[i].valor);
      }
      
      // Graphs
      const ctx = document.getElementById('myChart')
      // eslint-disable-next-line no-unused-vars
      const myChart = new Chart(ctx, {
        type: 'line',
        data: {
          labels: days,
          datasets: [{
            data: values,
            lineTension: 0,
            backgroundColor: 'transparent',
            borderColor: '#007bff',
            borderWidth: 4,
            pointBackgroundColor: '#007bff'
          }]
        },
        options: {
          scales: {
            yAxes: [{
              ticks: {
                beginAtZero: false
              }
            }]
          },
          legend: {
            display: false
          }
        }
      })
      
      
      //Rellenar tabla de las muestras de temperatura
      let tbodyRefTemp = document.getElementById("tabla_temperatura").getElementsByTagName("tbody")[0];
      for (const i in jsonObj.temperaturas) {
        const date = new Date(jsonObj.temperaturas[i].tiempo);
        
        // Insert a row at the end of table
        let row = tbodyRefTemp.insertRow();

        // Insert cells
        row.insertCell().innerHTML = (Number(i) + 1);
        row.insertCell().innerHTML = date.getFullYear();
        row.insertCell().innerHTML = date.getMonth();
        row.insertCell().innerHTML = date.getDate();
        row.insertCell().innerHTML = ('0' + date.getHours()).slice(-2) + ":" + ('0' + date.getMinutes()).slice(-2) + ":" + ('0' + date.getSeconds()).slice(-2);
        row.insertCell().innerHTML = (jsonObj.temperaturas[i].valor + " ºC");
        
      }
      
      
      
      //Rellenar tabla de las muestras de frecuencia cardiaca
      let tbodyRefFrec = document.getElementById("tabla_frecuencia_cardiaca").getElementsByTagName("tbody")[0];
      for (const i in jsonObj.frecuenciacardiaca) {
        const date = new Date(jsonObj.frecuenciacardiaca[i].tiempo);
        
        // Insert a row at the end of table
        let row = tbodyRefFrec.insertRow();

        // Insert cells
        row.insertCell().innerHTML = (Number(i) + 1);
        row.insertCell().innerHTML = date.getFullYear();
        row.insertCell().innerHTML = date.getMonth();
        row.insertCell().innerHTML = date.getDate();
        row.insertCell().innerHTML = ('0' + date.getHours()).slice(-2) + ":" + ('0' + date.getMinutes()).slice(-2) + ":" + ('0' + date.getSeconds()).slice(-2);
        row.insertCell().innerHTML = (jsonObj.frecuenciacardiaca[i].valor + " ppmin");
      }
    }
  };
  
  xhttp.open('GET', 'data', true);
  xhttp.send();



})()
