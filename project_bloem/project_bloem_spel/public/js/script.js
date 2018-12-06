const osc = require('osc');

const udpPort = new osc.UDPPort({
  localAddress: `localhost`,
  localPort: 12345
});



const gif1Button = document.querySelector(`#gif1Button`);
const gif1ButtonShow = document.querySelector(`#gif1ButtonShow`);
const gif1 = document.querySelector(`gif1`);

const clickOn = e => {
  console.log(e);
  gif1.classList.add(`hide`);

};

const clickToShow = e => {
  gif1.classList.remove(`hide`);
  console.log(e);
};


const init = () => {
  udpPort.open();
  udpPort.on(`message`, oscMsg => {
    console.log(oscMsg);
  });

  gif1Button.addEventListener(`click`, e => clickOn(e));
  gif1ButtonShow.addEventListener(`click`, e => clickToShow(e));

  
};
init();
