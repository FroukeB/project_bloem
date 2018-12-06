const gif1Button = document.querySelector(`#gif1Button`);
const gif1ButtonShow = document.querySelector(`#gif1ButtonShow`);
const gif1 = document.querySelector(`gif1`);

const clickOn = e => {
  document.getElementById("gif1").classList.add("hide");

};

const clickToShow = e => {
  document.getElementById("gif1").classList.remove("hide");

};


const init = () => {
  gif1Button.addEventListener(`click`, e => clickOn(e));
  gif1ButtonShow.addEventListener(`click`, e => clickToShow(e));
};
init();
