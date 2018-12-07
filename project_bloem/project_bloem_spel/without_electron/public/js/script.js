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
  gif1Button.addEventListener(`click`, e => clickOn(e));
  gif1ButtonShow.addEventListener(`click`, e => clickToShow(e));
};
init();
