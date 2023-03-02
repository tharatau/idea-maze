import { equal } from "node:assert";
import { after, describe, it } from "node:test";
import { dirname, relative, resolve } from "node:path";
import { cwd, platform } from "node:process";

import { By } from "selenium-webdriver";
import chrome from "selenium-webdriver/chrome.js";

const { Driver, ServiceBuilder, Options } = chrome;

export function customEventTest() {

  describe("custom events", async () => {

    let driver = undefined;

    it("crashes on custom event dispatch", async () => {
      const options = new Options();
      const args = [
        `--nwapp=${relative(
          cwd(),
          relative(cwd(), dirname(import.meta.url).slice(7))
        )}`,
        "--headless=new",
      ]
      options.addArguments(args);

      const chromedriverPath = resolve(cwd(), "node_modules", "nw", "nwjs", `chromedriver${platform === "win32" ? ".exe" : ""}`);

      const service = new ServiceBuilder(chromedriverPath).build();

      driver = Driver.createSession(options, service);

      const resultElement = await driver.findElement(By.id("result"));
      const result = await resultElement.getText();

      equal(result, "Custom event dispatched");
    });

    after(() => {
      driver.quit();
    });
  });
}