import { useState } from "react";

const ip4 = `${Math.floor(Math.random() * 255)}.${Math.floor(
  Math.random() * 255
)}.${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}`;

export function App(): JSX.Element {
  const pseudo = "ayush";
  const [pwd, setPwd] = useState("/");
  const [input, setInput] = useState("");
  const [commandHistory, setCommandHistory] = useState<string[]>([]);

  const handleInput = (event: any) => {
    setInput(event.target.value);
  };

  const handleCommand = (event: any) => {
    if (event.key === "Enter") {
      if (event.target.value === "clear") {
        setCommandHistory([]);
      } else if (event.target.value === "help") {
        setCommandHistory([...commandHistory,
        `${pseudo}@${ip4}:${pwd}$ ${input}`,
        `My name is ${pseudo} and this is my blog.`,
        `As you might have guessed, the theme is a terminal emulator.`,
        `I have a few commands that you can use to navigate around the site:`,
        ``,
        `clear: clear the terminal`,
        `help: list of valid commands in this terminal emulator`,
        `pwd: print the current working directory`,
      ]);
      } else if (event.target.value === "pwd") {
        setCommandHistory([
          ...commandHistory,
          `${pseudo}@${ip4}:${pwd}$ ${input}`,
          pwd,
        ]);
      } else {
        setCommandHistory([
          ...commandHistory,
          `${pseudo}@${ip4}:${pwd}$ ${input}`,
          `${input}: command not found`,
          `if you don't know what to do, type 'help'`,
        ]);
      }
      setInput("");
    }
  };

  return (
    <div>
      {commandHistory.map((command, idx) => (
        <div key={idx}>
          <span>{command}</span>
          <br />
        </div>
      ))}
      {`${pseudo}@${ip4}:${pwd}$ `}
      <input
        autoFocus={true}
        type="text"
        value={input}
        onChange={handleInput}
        onKeyDown={handleCommand}
      />
    </div>
  );
}
