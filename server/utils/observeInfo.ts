import type { Info } from "~/type";

const infoMap = new Map<number, (info: Info) => void>();

export function observeInfo(class_id: number) {
  return new Promise(r => infoMap.set(class_id, info => r(info)));
}

export function noticeInfo(class_id: number, info: Info) {
  infoMap.get(class_id)?.(info);
}
