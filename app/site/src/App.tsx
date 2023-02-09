import { useState } from "react";

const ip4 = `${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}`;

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
      setCommandHistory([...commandHistory, `${pseudo}@${ip4}:${pwd}$ ${input}`]);
    }
  }

  return (
    <div>
      {commandHistory.map((command) => (
        <>
        <span>{command}</span>
        <br />
        </>
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