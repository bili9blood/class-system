import { PrismaClient } from "@prisma/client";

const database = new PrismaClient();

export function useDatabase() {
  return database;
}
