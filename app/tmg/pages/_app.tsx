import type { AppProps } from 'next/app';

// Global styles go here
import "./index.scss";

function MyApp({ Component, pageProps }: AppProps) {
  return <Component {...pageProps} />
}

export default MyApp