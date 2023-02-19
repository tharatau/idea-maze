import { Carousal, Footer, Gallery, Header, Reviews } from "components";

import style from "./Home.module.scss";

const Home = (): JSX.Element => {
    return (
        <div className={style.home}>
            <Header />
            <Carousal />
            <Reviews />
            <Gallery />
            <Footer />
        </div>
    );
};

export default Home;