import VSX, { createEffect, createState } from "../../../src";

const Counter = (): HTMLElement => {
  let [count, setCount] = createState(0);

  createEffect(() => {
    console.log("Count: ", count().value);
  }, [count]);

  return (
    <>
      <button onClick={() => setCount((count().value as number) - 1)}>-</button>
      <span>{count}</span>
      <button onClick={() => setCount((count().value as number) + 1)}>+</button>
    </>
  );
};

export default Counter;
