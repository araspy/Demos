//import { createMuiTheme, ThemeProvider, makeStyles } from '@material-ui/core/styles';

import { ContactSupportOutlined } from '@material-ui/icons';
import ApexCharts from 'apexcharts'
import { useState, useEffect } from 'react'
//import './App.css';


let chart =null ;

function LineChart1() {
  //const classes = styles(); 
  //const [buttonPopup, setButtonPopup] = useState(false);  //for settings button. currently not working
  const [series, setSeries] = useState([{name:"", data:[]}]);
  const [entries, setEntries] = useState([]);
  const[options, setOptions]= useState({});
  let optionsTemp= {
    chart: {
      height: 350,
      width: '100%',
      margin: 'auto', 
      type: 'line',
      zoom: {
        enabled: false
      }
    },
    series: series,
    dataLabels: {
      enabled: false
    },
    stroke: {
      curve: 'straight'
    },
    title: {
      text: 'Product Trends by Entry',
      align: 'center'
    },
    grid: {
      row: {
        colors: ['#f3f3f3', 'transparent'], // takes an array which will be repeated on columns
        opacity: 0.5
      },
    },
    xaxis: {
      categories: entries,
    }
  }

  useEffect (()=>{
    console.log("user effect");
    loadData();
  },[])
  const [totals, setTotals]=useState({lemon:0, blue:0, punch:0});  //Total_Lemon, Total_Blue, Total_punch
  const loadData = async ()=>{
//alert("load data");
      // [{"StoreID":10,"StoreName":"Ted's BBQ","MachineID":10,"MachineStatus":"Active","NextMaintenance":"4/25/2022","Total_Lemon":21,"Total_Blue":15,"Total_Punch":18,"Rem_Lemon":7,"Rem_Blue":3,"Rem_Punch":2,"Flavor":"Lemonade","Size":1,"TimeDisp":"4/20/2022 5:18"}]
      const response =await fetch ("http://localhost:4000/overall");
      console.log("response", response);
     const data = await response.json();
console.log("DATA:", data)
      let series = [
          {
          name: "Blue",
          data:[] 
        },
        {
          name: "Lemon",
          data:[] 
        },
        {
          name: "Punch",
          data: []
        }
      ];
      let entries=[];
      let count=0;

      for (let i in data){
        const element = data[i];
        console.log("ELEMENT", element);
        series[0].data.push(element.Total_Blue);
        series[1].data.push(element.Total_Lemon);
        series[2].data.push(element.Total_Punch);
        count+=1;
        entries.push(count);

      }
      optionsTemp.series=series;
      optionsTemp.categories=entries;
      setOptions(optionsTemp);
     console.log("series", series);
     console.log("entries", entries);
      setSeries(series);
      setEntries(entries);
      chart = new ApexCharts(document.querySelector('#chart2'), optionsTemp);
      chart.render();
      console.log("rendered");
     // setTotals(totals);
  }


  let options1 = {
	chart:{
		type: 'line'
	},
	series: series,
	
	xaxis: {
		heights:entries
	}
}


      
    
  //Chart 1 Options
  console.log("OPTIONS!!!", options);
  //init chart

  //render chart
 
  return (
   
      <div id="chart2"></div>
  
  );
  
  }
export default LineChart1;