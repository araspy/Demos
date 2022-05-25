//import { createMuiTheme, ThemeProvider, makeStyles } from '@material-ui/core/styles';

import { CenterFocusStrong } from '@material-ui/icons';
import ApexCharts from 'apexcharts'
import { useState, useEffect } from 'react'
//import './App.css';


let chart = null;

function SummaryChart() {
  //const classes = styles(); 
  //const [buttonPopup, setButtonPopup] = useState(false);  //for settings button. currently not working
  const [values, setValues] = useState([0,0,0]);
  const [flavors, setFlavors] = useState(["Blue", "Lemon", "Punch"]);
  const[options, setOptions]= useState({});
  let optionsTemp = {
    chart: {
    height: 450,
    width: '100%',
    type: 'bar',
    background: '#f4f4f4',
    foreColor: '#333'
    },
    series: [
    {
      name: 'Population',
      data: values //array of ints
    }
  ],
    xaxis: {
      categories: flavors //array of strs
    },
    title: {
      text: "Total Sales by Product",
      align: "center",
      margin: 20,
      offsetY: 20,
      style: {
        fontSize: "50px"
      }
    }
  };

  useEffect (()=>{
    loadData();
  },[])
  const [totals, setTotals]=useState({lemon:0, blue:0, punch:0});  //Total_Lemon, Total_Blue, Total_punch
  const loadData = async ()=>{
//alert("load data"); for debugging to make sure loadData is actually being called
      // [{"StoreID":10,"StoreName":"Ted's BBQ","MachineID":10,"MachineStatus":"Active","NextMaintenance":"4/25/2022","Total_Lemon":21,"Total_Blue":15,"Total_Punch":18,"Rem_Lemon":7,"Rem_Blue":3,"Rem_Punch":2,"Flavor":"Lemonade","Size":1,"TimeDisp":"4/20/2022 5:18"}]
      const response =await fetch ("http://localhost:4000/popular");
      console.log("response", response);
      const data = await response.json();
      const totals ={lemon:data[0].Total_Lemon, blue:data[0].Total_Blue, punch:data[0].Total_Punch};
      const values = [data[0].Total_Blue, data[0].Total_Lemon, data[0].Total_Punch];
      optionsTemp.series[0].data=values;
      setValues(values);
      setOptions(optionsTemp);
      console.log("SummaryChart.options", options);
     
      chart = new ApexCharts(document.querySelector('#summaryChart'), optionsTemp);
      chart.render();
     // setTotals(totals);
  }
  //begin chart code 
  /*
    data = [
      {flavor: "Blue", value:100},   
      {flavor: "Lemon", value:200},

    ];
    let values=[];
    let flavors=[]'
    
    data.forEach ((row)={
      flavors.push(row.flavor);
      values.push(row.value);
    });
    setValues(values);
    setFlavors(flavors);

  */

  //Chart 1 Options
  
  console.log("OPTIONS: ",options)
  //init chart

  //render chart
 
  return (
   
      <div id="summaryChart"></div>
  
  );
}

export default SummaryChart;